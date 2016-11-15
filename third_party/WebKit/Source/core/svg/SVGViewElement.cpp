/*
 * Copyright (C) 2004, 2005, 2008 Nikolas Zimmermann <zimmermann@kde.org>
 * Copyright (C) 2004, 2005, 2007 Rob Buis <buis@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "core/svg/SVGViewElement.h"

#include "core/SVGNames.h"
#include "core/frame/UseCounter.h"
#include "core/svg/SVGStaticStringList.h"

namespace blink {

inline SVGViewElement::SVGViewElement(Document& document)
    : SVGElement(SVGNames::viewTag, document),
      SVGFitToViewBox(this),
      m_viewTarget(
          SVGStaticStringList::create(this, SVGNames::viewTargetAttr)) {
  addToPropertyMap(m_viewTarget);
  UseCounter::count(document, UseCounter::SVGViewElement);
}

DEFINE_NODE_FACTORY(SVGViewElement)

DEFINE_TRACE(SVGViewElement) {
  visitor->trace(m_viewTarget);
  SVGElement::trace(visitor);
  SVGFitToViewBox::trace(visitor);
}

SVGStringListTearOff* SVGViewElement::viewTarget() {
  return m_viewTarget->tearOff();
}

void SVGViewElement::parseAttribute(const QualifiedName& name,
                                    const AtomicString& oldValue,
                                    const AtomicString& value) {
  if (SVGZoomAndPan::parseAttribute(name, value))
    return;

  SVGElement::parseAttribute(name, oldValue, value);
}

}  // namespace blink