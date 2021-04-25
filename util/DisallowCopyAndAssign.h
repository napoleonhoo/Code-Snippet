#ifndef NPJH_UTIL_DISALLOW_COPY_AND_ASSIGN_H_
#define NPJH_UTIL_DISALLOW_COPY_AND_ASSIGN_H_ 

namespace npjh {

#define    DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);                \
    TypeName& operator=(const TypeName&)
    
}

#endif