//
//  SwiftMetadata.hpp
//  BlankApp
//
//  Created by Teodor Dermendzhiev on 15.03.20.
//

#ifndef SwiftMetadata_hpp
#define SwiftMetadata_hpp

#include <stdio.h>
#include <string>
#include <JavaScriptCore/JSGlobalObject.h>

#include <JavaScriptCore/runtime/JSONObject.h>

struct SwiftMeta {
    std::string name;
    std::string usr;
    
    static const char* findSymbol(StringImpl* symbolName);
    RefPtr<JSON::Array> instance();
    static bool setSwiftMetadata(RefPtr<JSON::Array> meta);
};

struct MethodSwiftMeta: SwiftMeta {
    
};

struct FunctionSwiftMeta: SwiftMeta {
    
};

struct BaseClassSwiftMeta: SwiftMeta {
    
};

#endif /* SwiftMetadata_hpp */
