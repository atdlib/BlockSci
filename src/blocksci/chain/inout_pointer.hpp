//
//  inout_pointer.hpp
//  blocksci
//
//  Created by Harry Kalodner on 9/4/17.
//
//

#ifndef inout_pointer_hpp
#define inout_pointer_hpp

#include "chain_fwd.hpp"

#include <vector>
#include <cstdint>
#include <string>

namespace blocksci {
    class DataAccess;
    
    struct InoutPointer {
        uint32_t txNum;
        uint16_t inoutNum;
        
        InoutPointer() : txNum(0), inoutNum(0) {}
        InoutPointer(uint32_t txNum_, uint16_t inoutNum_) : txNum(txNum_), inoutNum(inoutNum_) {}
        
        bool operator==(const InoutPointer& other) const {
            return txNum == other.txNum && inoutNum == other.inoutNum;
        }
        
        bool operator!=(const InoutPointer& other) const {
            return txNum != other.txNum || inoutNum != other.inoutNum;
        }
    };
    
    struct InputPointer : public InoutPointer {
        using InoutPointer::InoutPointer;
        
        bool operator<(const InputPointer& other) const {
            if (txNum != other.txNum) {
                return txNum < other.txNum;
            } else {
                return inoutNum < other.inoutNum;
            }
        }
        
        bool isValid(const ChainAccess &access) const;
        
        std::string toString() const;
    };
    
    struct OutputPointer : public InoutPointer {
        using InoutPointer::InoutPointer;
        
        bool operator<(const OutputPointer& other) const {
            if (txNum != other.txNum) {
                return txNum < other.txNum;
            } else {
                return inoutNum < other.inoutNum;
            }
        }
        
        bool isValid(const ChainAccess &access) const;
        
        std::string toString() const;
    };
    
    uint64_t calculateBalance(const std::vector<OutputPointer> &pointers, BlockHeight height, const DataAccess &access);
    std::vector<Output> getOutputs(const std::vector<OutputPointer> &pointers, const DataAccess &access);
    std::vector<Input> getInputs(const std::vector<OutputPointer> &pointers, const DataAccess &access);
    std::vector<Transaction> getTransactions(const std::vector<OutputPointer> &pointers, const DataAccess &access);
    std::vector<Transaction> getOutputTransactions(const std::vector<OutputPointer> &pointers, const DataAccess &access);
    std::vector<Transaction> getInputTransactions(const std::vector<OutputPointer> &pointers, const DataAccess &access);
}

std::ostream &operator<<(std::ostream &os, const blocksci::InputPointer &pointer);
std::ostream &operator<<(std::ostream &os, const blocksci::OutputPointer &pointer);

namespace std {
    template<> struct hash<blocksci::InputPointer> {
        size_t operator()(const blocksci::InputPointer &pointer) const;
    };
    template<> struct hash<blocksci::OutputPointer> {
        size_t operator()(const blocksci::OutputPointer &pointer) const;
    };
}

#endif /* inout_pointer_hpp */
