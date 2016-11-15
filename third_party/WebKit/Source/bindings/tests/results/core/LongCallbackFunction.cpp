// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

// clang-format off

#include "LongCallbackFunction.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/ScriptState.h"
#include "bindings/core/v8/ToV8.h"
#include "bindings/core/v8/V8Binding.h"
#include "core/dom/ExecutionContext.h"
#include "wtf/Assertions.h"

namespace blink {

LongCallbackFunction::LongCallbackFunction(ScriptState* scriptState, v8::Local<v8::Function> callback)
    : m_scriptState(scriptState),
    m_callback(scriptState->isolate(), callback) {
  DCHECK(!m_callback.isEmpty());
  m_callback.setPhantom();
}

DEFINE_TRACE(LongCallbackFunction) {}

DEFINE_TRACE_WRAPPERS(LongCallbackFunction) {
  visitor->traceWrappers(&m_callback.cast<v8::Object>());
}

bool LongCallbackFunction::call(ScriptWrappable* scriptWrappable, int num1, int num2, int& returnValue) {
  if (!m_scriptState->contextIsValid())
    return false;

  ExecutionContext* context = m_scriptState->getExecutionContext();
  DCHECK(context);
  if (context->activeDOMObjectsAreSuspended() || context->activeDOMObjectsAreStopped())
    return false;

  if (m_callback.isEmpty())
    return false;

  // TODO(bashi): Make sure that using TrackExceptionState is OK.
  // crbug.com/653769
  TrackExceptionState exceptionState;
  ScriptState::Scope scope(m_scriptState.get());

  v8::Local<v8::Value> num1Argument = v8::Integer::New(m_scriptState->isolate(), num1);
  v8::Local<v8::Value> num2Argument = v8::Integer::New(m_scriptState->isolate(), num2);

  v8::Local<v8::Value> thisValue = toV8(scriptWrappable, m_scriptState->context()->Global(), m_scriptState->isolate());

  v8::Local<v8::Value> argv[] = { num1Argument, num2Argument };

  v8::Local<v8::Value> v8ReturnValue;
  v8::TryCatch exceptionCatcher(m_scriptState->isolate());
  exceptionCatcher.SetVerbose(true);

  if (V8ScriptRunner::callFunction(m_callback.newLocal(m_scriptState->isolate()), m_scriptState->getExecutionContext(), thisValue, 2, argv, m_scriptState->isolate()).ToLocal(&v8ReturnValue)) {
    int cppValue = toInt32(m_scriptState->isolate(), v8ReturnValue, NormalConversion, exceptionState);
        if (exceptionState.hadException())
          return false;
    returnValue = cppValue;
    return true;
  }
  return false;
}

}  // namespace blink