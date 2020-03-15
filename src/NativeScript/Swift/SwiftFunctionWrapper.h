//
//  SwiftFunctionWrapper.h
//  NativeScript
//



#include "FFICall.h"
#include "FunctionWrapper.h"

namespace NativeScript {

class SwiftFunctionWrapper : public FunctionWrapper {
public:
    typedef FunctionWrapper Base;

    static JSC::Strong<SwiftFunctionWrapper> create(JSC::VM& vm, JSC::Structure* structure, void* functionPointer, const WTF::String& name, JSC::JSCell* returnType, const WTF::Vector<JSC::Strong<JSC::JSCell>>& parameterTypes, bool retainsReturnedCocoaObjects) {
        JSC::Strong<SwiftFunctionWrapper> function(vm, new (NotNull, JSC::allocateCell<SwiftFunctionWrapper>(vm.heap)) SwiftFunctionWrapper(vm, structure));
        function->finishCreation(vm, functionPointer, name, returnType, parameterTypes, retainsReturnedCocoaObjects);
        return function;
    }

    DECLARE_INFO;

    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype) {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::InternalFunctionType, StructureFlags), info());
    }

    void* functionPointer() {
        return static_cast<SwiftFunctionCall*>(this->onlyFuncInContainer())->functionPointer();
    }

private:
    SwiftFunctionWrapper(JSC::VM& vm, JSC::Structure* structure)
        : Base(vm, structure) {
    }

    void finishCreation(JSC::VM&, void* functionPointer, const WTF::String& name, JSC::JSCell* returnType, const WTF::Vector<JSC::Strong<JSC::JSCell>>& parameterTypes, bool retainsReturnedCocoaObjects);

    static void destroy(JSC::JSCell* cell) {
        static_cast<SwiftFunctionWrapper*>(cell)->~SwiftFunctionWrapper();
    }

    static void preInvocation(FFICall*, JSC::ExecState*, FFICall::Invocation&);
    static void postInvocation(FFICall*, JSC::ExecState*, FFICall::Invocation&);
};

class SwiftFunctionCall : public FFICall {

public:
    SwiftFunctionCall(FunctionWrapper* owner, void* functionPointer, bool retainsReturnedCocoaObjects)
        : FFICall(owner)
        , _functionPointer(functionPointer)
        , _retainsReturnedCocoaObjects(retainsReturnedCocoaObjects) {
    }

    DECLARE_INFO;

    template <typename CellType, JSC::SubspaceAccess mode>
    static JSC::IsoSubspace* subspaceFor(JSC::VM& vm) {
        return &vm.tnsSwiftFunctionWrapperSpace;
    }

    void* functionPointer() const {
        return this->_functionPointer;
    }
    bool retainsReturnedCocoaObjects() const {
        return this->_retainsReturnedCocoaObjects;
    }

private:
    void* _functionPointer;

    bool _retainsReturnedCocoaObjects;
};

} // namespace NativeScript

