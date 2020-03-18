//
//  SwiftMetadata.cpp
//  BlankApp
//
//  Created by Teodor Dermendzhiev on 15.03.20.
//

#include "SwiftMetadata.hpp"
#include <string>
#include <iostream>

static RefPtr<JSON::Array> metaFileInstance(nullptr);

const char* SwiftMeta::findSymbol(StringImpl* symbolName) {
                for (auto it = metaFileInstance->begin(); it!= metaFileInstance->end(); ++it) {
                    RefPtr<JSON::Value> v = *it;
                    RefPtr<JSON::Object> meta;
                    if (v->asObject(meta)) {
                        WTF::String kind;
                        if (meta->getString(WTF::String("name"), kind)) {
//                            std::cout << kind.characters8();X
//                            std::cout << symbolName->characters8() << "=" << kind.characters8() << "\n";
                            if (std::strcmp(reinterpret_cast<const char*>(symbolName->characters8()), reinterpret_cast<const char*>(kind.characters8())) == 0) {
//                                std::cout << symbolName->characters8() << "=" << kind.characters8() << "\n";
                                WTF::String usr;
                                if (meta->getString(WTF::String("usr"), usr)) {
                                    StringBuilder output;
                                    output.append("$s8Gameraww");
                                    output.append(reinterpret_cast<const char*>(usr.characters8()));
                                    return reinterpret_cast<const char*>(output.characters8());
                                }
                                
                            }
                        }
                    } else {
                        //throw not an object
                    }
                }
    return nullptr;
}



bool SwiftMeta::setSwiftMetadata(RefPtr<JSON::Array> meta) {
    metaFileInstance = meta;
    return true;
}

RefPtr<JSON::Array> SwiftMeta::instance() {
    return metaFileInstance;
}
