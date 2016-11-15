// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

// clang-format off
#include "V8TestInterfaceNode.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/GeneratedCodeHelper.h"
#include "bindings/core/v8/V8AbstractEventListener.h"
#include "bindings/core/v8/V8DOMConfiguration.h"
#include "bindings/core/v8/V8EventListenerHelper.h"
#include "bindings/core/v8/V8ObjectConstructor.h"
#include "bindings/core/v8/V8TestInterfaceEmpty.h"
#include "core/HTMLNames.h"
#include "core/dom/Document.h"
#include "core/dom/custom/V0CustomElementProcessingStack.h"
#include "wtf/GetPtr.h"
#include "wtf/RefPtr.h"

namespace blink {

// Suppress warning: global constructors, because struct WrapperTypeInfo is trivial
// and does not depend on another global objects.
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
const WrapperTypeInfo V8TestInterfaceNode::wrapperTypeInfo = { gin::kEmbedderBlink, V8TestInterfaceNode::domTemplate, V8TestInterfaceNode::trace, V8TestInterfaceNode::traceWrappers, 0, nullptr, "TestInterfaceNode", &V8Node::wrapperTypeInfo, WrapperTypeInfo::WrapperTypeObjectPrototype, WrapperTypeInfo::NodeClassId, WrapperTypeInfo::NotInheritFromActiveScriptWrappable, WrapperTypeInfo::InheritFromEventTarget, WrapperTypeInfo::Dependent };
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic pop
#endif

// This static member must be declared by DEFINE_WRAPPERTYPEINFO in TestInterfaceNode.h.
// For details, see the comment of DEFINE_WRAPPERTYPEINFO in
// bindings/core/v8/ScriptWrappable.h.
const WrapperTypeInfo& TestInterfaceNode::s_wrapperTypeInfo = V8TestInterfaceNode::wrapperTypeInfo;

// not [ActiveScriptWrappable]
static_assert(
    !std::is_base_of<ActiveScriptWrappable, TestInterfaceNode>::value,
    "TestInterfaceNode inherits from ActiveScriptWrappable, but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");
static_assert(
    std::is_same<decltype(&TestInterfaceNode::hasPendingActivity),
                 decltype(&ScriptWrappable::hasPendingActivity)>::value,
    "TestInterfaceNode is overriding hasPendingActivity(), but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");

namespace TestInterfaceNodeV8Internal {

static void nodeNameAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(holder);

  v8SetReturnValueString(info, impl->nodeName(), info.GetIsolate());
}

void nodeNameAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceNodeV8Internal::nodeNameAttributeGetter(info);
}

static void nodeNameAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();
  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(holder);

  // Prepare the value to be set.
  V8StringResource<> cppValue = v8Value;
  if (!cppValue.prepare())
    return;

  impl->setNodeName(cppValue);
}

void nodeNameAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Value> v8Value = info[0];

  TestInterfaceNodeV8Internal::nodeNameAttributeSetter(v8Value, info);
}

static void stringAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(holder);

  v8SetReturnValueString(info, impl->stringAttribute(), info.GetIsolate());
}

void stringAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceNodeV8Internal::stringAttributeAttributeGetter(info);
}

static void stringAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();
  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(holder);

  // Prepare the value to be set.
  V8StringResource<> cppValue = v8Value;
  if (!cppValue.prepare())
    return;

  impl->setStringAttribute(cppValue);
}

void stringAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Value> v8Value = info[0];

  TestInterfaceNodeV8Internal::stringAttributeAttributeSetter(v8Value, info);
}

static void readonlyTestInterfaceEmptyAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(holder);

  v8SetReturnValueFast(info, WTF::getPtr(impl->readonlyTestInterfaceEmptyAttribute()), impl);
}

void readonlyTestInterfaceEmptyAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceNodeV8Internal::readonlyTestInterfaceEmptyAttributeAttributeGetter(info);
}

static void eventHandlerAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(holder);

  EventListener* cppValue(WTF::getPtr(impl->eventHandlerAttribute()));

  v8SetReturnValue(info, cppValue ? V8AbstractEventListener::cast(cppValue)->getListenerOrNull(info.GetIsolate(), impl->getExecutionContext()) : v8::Null(info.GetIsolate()).As<v8::Value>());
}

void eventHandlerAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceNodeV8Internal::eventHandlerAttributeAttributeGetter(info);
}

static void eventHandlerAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();
  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(holder);

  // Prepare the value to be set.

  impl->setEventHandlerAttribute(V8EventListenerHelper::getEventListener(ScriptState::forReceiverObject(info), v8Value, true, ListenerFindOrCreate));
}

void eventHandlerAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Value> v8Value = info[0];

  TestInterfaceNodeV8Internal::eventHandlerAttributeAttributeSetter(v8Value, info);
}

static void perWorldBindingsReadonlyTestInterfaceEmptyAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(holder);

  v8SetReturnValueFast(info, WTF::getPtr(impl->perWorldBindingsReadonlyTestInterfaceEmptyAttribute()), impl);
}

void perWorldBindingsReadonlyTestInterfaceEmptyAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceNodeV8Internal::perWorldBindingsReadonlyTestInterfaceEmptyAttributeAttributeGetter(info);
}

static void perWorldBindingsReadonlyTestInterfaceEmptyAttributeAttributeGetterForMainWorld(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(holder);

  v8SetReturnValueForMainWorld(info, WTF::getPtr(impl->perWorldBindingsReadonlyTestInterfaceEmptyAttribute()));
}

void perWorldBindingsReadonlyTestInterfaceEmptyAttributeAttributeGetterCallbackForMainWorld(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceNodeV8Internal::perWorldBindingsReadonlyTestInterfaceEmptyAttributeAttributeGetterForMainWorld(info);
}

static void reflectStringAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(holder);

  v8SetReturnValueString(info, impl->fastGetAttribute(HTMLNames::reflectstringattributeAttr), info.GetIsolate());
}

void reflectStringAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceNodeV8Internal::reflectStringAttributeAttributeGetter(info);
}

static void reflectStringAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();
  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(holder);

  // Prepare the value to be set.
  V8StringResource<> cppValue = v8Value;
  if (!cppValue.prepare())
    return;

  impl->setAttribute(HTMLNames::reflectstringattributeAttr, cppValue);
}

void reflectStringAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Value> v8Value = info[0];

  V0CustomElementProcessingStack::CallbackDeliveryScope deliveryScope;

  TestInterfaceNodeV8Internal::reflectStringAttributeAttributeSetter(v8Value, info);
}

static void reflectUrlStringAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(holder);

  v8SetReturnValueString(info, impl->getURLAttribute(HTMLNames::reflecturlstringattributeAttr), info.GetIsolate());
}

void reflectUrlStringAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceNodeV8Internal::reflectUrlStringAttributeAttributeGetter(info);
}

static void reflectUrlStringAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();
  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(holder);

  // Prepare the value to be set.
  V8StringResource<> cppValue = v8Value;
  if (!cppValue.prepare())
    return;

  impl->setAttribute(HTMLNames::reflecturlstringattributeAttr, cppValue);
}

void reflectUrlStringAttributeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Value> v8Value = info[0];

  V0CustomElementProcessingStack::CallbackDeliveryScope deliveryScope;

  TestInterfaceNodeV8Internal::reflectUrlStringAttributeAttributeSetter(v8Value, info);
}

static void testInterfaceEmptyMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(info.Holder());

  v8SetReturnValueFast(info, impl->testInterfaceEmptyMethod(), impl);
}

void testInterfaceEmptyMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceNodeV8Internal::testInterfaceEmptyMethodMethod(info);
}

static void perWorldBindingsTestInterfaceEmptyMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(info.Holder());

  v8SetReturnValueFast(info, impl->perWorldBindingsTestInterfaceEmptyMethod(), impl);
}

void perWorldBindingsTestInterfaceEmptyMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceNodeV8Internal::perWorldBindingsTestInterfaceEmptyMethodMethod(info);
}

static void perWorldBindingsTestInterfaceEmptyMethodMethodForMainWorld(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(info.Holder());

  v8SetReturnValueForMainWorld(info, impl->perWorldBindingsTestInterfaceEmptyMethod());
}

void perWorldBindingsTestInterfaceEmptyMethodMethodCallbackForMainWorld(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceNodeV8Internal::perWorldBindingsTestInterfaceEmptyMethodMethodForMainWorld(info);
}

static void perWorldBindingsTestInterfaceEmptyMethodOptionalBooleanArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "TestInterfaceNode", "perWorldBindingsTestInterfaceEmptyMethodOptionalBooleanArg");

  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(info.Holder());

  bool optionalBooleanArgument;
  int numArgsPassed = info.Length();
  while (numArgsPassed > 0) {
    if (!info[numArgsPassed - 1]->IsUndefined())
      break;
    --numArgsPassed;
  }
  if (UNLIKELY(numArgsPassed <= 0)) {
    v8SetReturnValueFast(info, impl->perWorldBindingsTestInterfaceEmptyMethodOptionalBooleanArg(), impl);
    return;
  }
  optionalBooleanArgument = toBoolean(info.GetIsolate(), info[0], exceptionState);
  if (exceptionState.hadException())
    return;

  v8SetReturnValueFast(info, impl->perWorldBindingsTestInterfaceEmptyMethodOptionalBooleanArg(optionalBooleanArgument), impl);
}

void perWorldBindingsTestInterfaceEmptyMethodOptionalBooleanArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceNodeV8Internal::perWorldBindingsTestInterfaceEmptyMethodOptionalBooleanArgMethod(info);
}

static void perWorldBindingsTestInterfaceEmptyMethodOptionalBooleanArgMethodForMainWorld(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "TestInterfaceNode", "perWorldBindingsTestInterfaceEmptyMethodOptionalBooleanArg");

  TestInterfaceNode* impl = V8TestInterfaceNode::toImpl(info.Holder());

  bool optionalBooleanArgument;
  int numArgsPassed = info.Length();
  while (numArgsPassed > 0) {
    if (!info[numArgsPassed - 1]->IsUndefined())
      break;
    --numArgsPassed;
  }
  if (UNLIKELY(numArgsPassed <= 0)) {
    v8SetReturnValueForMainWorld(info, impl->perWorldBindingsTestInterfaceEmptyMethodOptionalBooleanArg());
    return;
  }
  optionalBooleanArgument = toBoolean(info.GetIsolate(), info[0], exceptionState);
  if (exceptionState.hadException())
    return;

  v8SetReturnValueForMainWorld(info, impl->perWorldBindingsTestInterfaceEmptyMethodOptionalBooleanArg(optionalBooleanArgument));
}

void perWorldBindingsTestInterfaceEmptyMethodOptionalBooleanArgMethodCallbackForMainWorld(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestInterfaceNodeV8Internal::perWorldBindingsTestInterfaceEmptyMethodOptionalBooleanArgMethodForMainWorld(info);
}

} // namespace TestInterfaceNodeV8Internal

const V8DOMConfiguration::AccessorConfiguration V8TestInterfaceNodeAccessors[] = {
    {"nodeName", TestInterfaceNodeV8Internal::nodeNameAttributeGetterCallback, TestInterfaceNodeV8Internal::nodeNameAttributeSetterCallback, 0, 0, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder},
    {"stringAttribute", TestInterfaceNodeV8Internal::stringAttributeAttributeGetterCallback, TestInterfaceNodeV8Internal::stringAttributeAttributeSetterCallback, 0, 0, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder},
    {"readonlyTestInterfaceEmptyAttribute", TestInterfaceNodeV8Internal::readonlyTestInterfaceEmptyAttributeAttributeGetterCallback, 0, 0, 0, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder},
    {"eventHandlerAttribute", TestInterfaceNodeV8Internal::eventHandlerAttributeAttributeGetterCallback, TestInterfaceNodeV8Internal::eventHandlerAttributeAttributeSetterCallback, 0, 0, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder},
    {"perWorldBindingsReadonlyTestInterfaceEmptyAttribute", TestInterfaceNodeV8Internal::perWorldBindingsReadonlyTestInterfaceEmptyAttributeAttributeGetterCallback, 0, TestInterfaceNodeV8Internal::perWorldBindingsReadonlyTestInterfaceEmptyAttributeAttributeGetterCallbackForMainWorld, 0, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder},
    {"reflectStringAttribute", TestInterfaceNodeV8Internal::reflectStringAttributeAttributeGetterCallback, TestInterfaceNodeV8Internal::reflectStringAttributeAttributeSetterCallback, 0, 0, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder},
    {"reflectUrlStringAttribute", TestInterfaceNodeV8Internal::reflectUrlStringAttributeAttributeGetterCallback, TestInterfaceNodeV8Internal::reflectUrlStringAttributeAttributeSetterCallback, 0, 0, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder},
};

const V8DOMConfiguration::MethodConfiguration V8TestInterfaceNodeMethods[] = {
    {"testInterfaceEmptyMethod", TestInterfaceNodeV8Internal::testInterfaceEmptyMethodMethodCallback, 0, 0, v8::None, V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnPrototype},
    {"perWorldBindingsTestInterfaceEmptyMethod", TestInterfaceNodeV8Internal::perWorldBindingsTestInterfaceEmptyMethodMethodCallback, TestInterfaceNodeV8Internal::perWorldBindingsTestInterfaceEmptyMethodMethodCallbackForMainWorld, 0, v8::None, V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnPrototype},
    {"perWorldBindingsTestInterfaceEmptyMethodOptionalBooleanArg", TestInterfaceNodeV8Internal::perWorldBindingsTestInterfaceEmptyMethodOptionalBooleanArgMethodCallback, TestInterfaceNodeV8Internal::perWorldBindingsTestInterfaceEmptyMethodOptionalBooleanArgMethodCallbackForMainWorld, 0, v8::None, V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnPrototype},
};

static void installV8TestInterfaceNodeTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world, v8::Local<v8::FunctionTemplate> interfaceTemplate) {
  // Initialize the interface object's template.
  V8DOMConfiguration::initializeDOMInterfaceTemplate(isolate, interfaceTemplate, V8TestInterfaceNode::wrapperTypeInfo.interfaceName, V8Node::domTemplate(isolate, world), V8TestInterfaceNode::internalFieldCount);
  v8::Local<v8::Signature> signature = v8::Signature::New(isolate, interfaceTemplate);
  ALLOW_UNUSED_LOCAL(signature);
  v8::Local<v8::ObjectTemplate> instanceTemplate = interfaceTemplate->InstanceTemplate();
  ALLOW_UNUSED_LOCAL(instanceTemplate);
  v8::Local<v8::ObjectTemplate> prototypeTemplate = interfaceTemplate->PrototypeTemplate();
  ALLOW_UNUSED_LOCAL(prototypeTemplate);
  // Register DOM constants, attributes and operations.
  V8DOMConfiguration::installAccessors(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8TestInterfaceNodeAccessors, WTF_ARRAY_LENGTH(V8TestInterfaceNodeAccessors));
  V8DOMConfiguration::installMethods(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8TestInterfaceNodeMethods, WTF_ARRAY_LENGTH(V8TestInterfaceNodeMethods));
}

v8::Local<v8::FunctionTemplate> V8TestInterfaceNode::domTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world) {
  return V8DOMConfiguration::domClassTemplate(isolate, world, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), installV8TestInterfaceNodeTemplate);
}

bool V8TestInterfaceNode::hasInstance(v8::Local<v8::Value> v8Value, v8::Isolate* isolate) {
  return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Local<v8::Object> V8TestInterfaceNode::findInstanceInPrototypeChain(v8::Local<v8::Value> v8Value, v8::Isolate* isolate) {
  return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

TestInterfaceNode* V8TestInterfaceNode::toImplWithTypeCheck(v8::Isolate* isolate, v8::Local<v8::Value> value) {
  return hasInstance(value, isolate) ? toImpl(v8::Local<v8::Object>::Cast(value)) : nullptr;
}

}  // namespace blink