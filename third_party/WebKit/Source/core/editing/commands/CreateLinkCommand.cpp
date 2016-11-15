/*
 * Copyright (C) 2006 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "core/editing/commands/CreateLinkCommand.h"

#include "core/dom/Text.h"
#include "core/html/HTMLAnchorElement.h"

namespace blink {

CreateLinkCommand::CreateLinkCommand(Document& document, const String& url)
    : CompositeEditCommand(document) {
  m_url = url;
}

void CreateLinkCommand::doApply(EditingState* editingState) {
  if (endingSelection().isNone())
    return;

  HTMLAnchorElement* anchorElement = HTMLAnchorElement::create(document());
  anchorElement->setHref(AtomicString(m_url));

  if (endingSelection().isRange()) {
    applyStyledElement(anchorElement, editingState);
    if (editingState->isAborted())
      return;
  } else {
    insertNodeAt(anchorElement, endingSelection().start(), editingState);
    if (editingState->isAborted())
      return;
    Text* textNode = Text::create(document(), m_url);
    appendNode(textNode, anchorElement, editingState);
    if (editingState->isAborted())
      return;
    setEndingSelection(
        SelectionInDOMTree::Builder()
            .collapse(Position::inParentBeforeNode(*anchorElement))
            .extend(Position::inParentAfterNode(*anchorElement))
            .setIsDirectional(endingSelection().isDirectional())
            .build());
  }
}

InputEvent::InputType CreateLinkCommand::inputType() const {
  return InputEvent::InputType::CreateLink;
}

}  // namespace blink