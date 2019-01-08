//
//  RecordPrototype.h
//  NativeScript
//
//  Created by Jason Zhekov on 9/29/14.
//  Copyright (c) 2014 Telerik. All rights reserved.
//

#ifndef __NativeScript__RecordPrototype__
#define __NativeScript__RecordPrototype__

namespace Metadata {
struct RecordMeta;
}

namespace NativeScript {
class RecordField;

class RecordPrototype : public JSC::JSDestructibleObject {
public:
    typedef JSC::JSDestructibleObject Base;

    static JSC::Strong<RecordPrototype> create(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::Structure* structure) {
        JSC::Strong<RecordPrototype> cell(vm, new (NotNull, JSC::allocateCell<RecordPrototype>(vm.heap)) RecordPrototype(vm, structure));
        cell->finishCreation(vm, globalObject);
        return cell;
    }

    DECLARE_INFO;

    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype) {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

    const WTF::Vector<JSC::WriteBarrier<RecordField>> fields() const {
        return this->_fields;
    }

    void setFields(JSC::VM&, GlobalObject*, const WTF::Vector<JSC::Strong<RecordField>>&);

private:
    RecordPrototype(JSC::VM& vm, JSC::Structure* structure)
        : Base(vm, structure) {
    }

    static void destroy(JSC::JSCell* cell) {
        static_cast<RecordPrototype*>(cell)->~RecordPrototype();
    }

    void finishCreation(JSC::VM&, JSC::JSGlobalObject*);

    static void visitChildren(JSC::JSCell* cell, JSC::SlotVisitor& visitor);

    WTF::Vector<JSC::WriteBarrier<RecordField>> _fields;
};
} // namespace NativeScript

#endif /* defined(__NativeScript__RecordPrototype__) */
