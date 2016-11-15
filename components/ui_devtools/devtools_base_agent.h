// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_UI_DEVTOOLS_DEVTOOLS_BASE_AGENT_H_
#define COMPONENTS_UI_DEVTOOLS_DEVTOOLS_BASE_AGENT_H_

#include "components/ui_devtools/Protocol.h"

namespace ui {
namespace devtools {

class UiDevToolsAgent {
 public:
  UiDevToolsAgent() {}
  virtual ~UiDevToolsAgent() {}

  virtual void Init(protocol::UberDispatcher*) = 0;
};

// A base agent so that any Backend implementation has access to the
// corresponding frontend instance. This also wires the backend with
// the dispatcher. When initializing an instance of this class,
// the template argument is simply the generated Metainfo class of
// any domain type such as DOM or CSS.
template <typename DomainMetainfo>
class UiDevToolsBaseAgent : public UiDevToolsAgent,
                            public DomainMetainfo::BackendClass {
 public:
  void Init(protocol::UberDispatcher* dispatcher) {
    frontend_.reset(
        new typename DomainMetainfo::FrontendClass(dispatcher->channel()));
    DomainMetainfo::DispatcherClass::wire(dispatcher, this);
  }

 protected:
  UiDevToolsBaseAgent() {}
  typename DomainMetainfo::FrontendClass* frontend() const {
    return frontend_.get();
  }

 private:
  std::unique_ptr<typename DomainMetainfo::FrontendClass> frontend_;

  DISALLOW_COPY_AND_ASSIGN(UiDevToolsBaseAgent);
};

}  // namespace devtools
}  // namespace ui

#endif  // COMPONENTS_UI_DEVTOOLS_DEVTOOLS_BASE_AGENT_H_