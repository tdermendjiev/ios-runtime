//
//  SwiftFunctionWrapper.cpp
//  NativeScript
//

#include "SwiftFunctionWrapper.h"

namespace NativeScript {
using namespace JSC;

const ClassInfo SwiftFunctionWrapper::s_info = { "SwiftFunctionWrapper", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(SwiftFunctionWrapper) };

void SwiftFunctionWrapper::finishCreation(VM& vm, void* functionPointer, const WTF::String& name, JSCell* returnType, const WTF::Vector<Strong<JSCell>>& parameterTypes, bool retainsReturnedCocoaObjects) {
    Base::finishCreation(vm, name);
    auto call = std::make_unique<SwiftFunctionCall>(this, functionPointer, retainsReturnedCocoaObjects);
    call->initializeFFI(vm, { &preInvocation, &postInvocation }, returnType, parameterTypes);
    this->_functionsContainer.push_back(std::move(call));
    Base::initializeFunctionWrapper(vm, parameterTypes.size());
}

void SwiftFunctionWrapper::preInvocation(FFICall* callee, ExecState*, FFICall::Invocation& invocation) {
    invocation.function = const_cast<void*>(static_cast<SwiftFunctionCall*>(callee)->functionPointer());
}

void SwiftFunctionWrapper::postInvocation(FFICall* callee, ExecState*, FFICall::Invocation& invocation) {
    SwiftFunctionCall* call = static_cast<SwiftFunctionCall*>(callee);
    if (call->retainsReturnedCocoaObjects()) {
        [invocation.getResult<id>() release];
    }
}
}
