// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "core/frame/csp/SourceListDirective.h"

#include "core/dom/Document.h"
#include "core/frame/csp/CSPSource.h"
#include "core/frame/csp/ContentSecurityPolicy.h"
#include "platform/network/ResourceRequest.h"
#include "platform/weborigin/KURL.h"
#include "platform/weborigin/SchemeRegistry.h"
#include "platform/weborigin/SecurityOrigin.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace blink {

class SourceListDirectiveTest : public ::testing::Test {
 public:
  SourceListDirectiveTest() : csp(ContentSecurityPolicy::create()) {}

 protected:
  virtual void SetUp() {
    KURL secureURL(ParsedURLString, "https://example.test/image.png");
    RefPtr<SecurityOrigin> secureOrigin(SecurityOrigin::create(secureURL));
    document = Document::create();
    document->setSecurityOrigin(secureOrigin);
    csp->bindToExecutionContext(document.get());
  }

  Persistent<ContentSecurityPolicy> csp;
  Persistent<Document> document;
};

TEST_F(SourceListDirectiveTest, BasicMatchingNone) {
  KURL base;
  String sources = "'none'";
  SourceListDirective sourceList("script-src", sources, csp.get());

  EXPECT_FALSE(sourceList.allows(KURL(base, "http://example.com/")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "https://example.test/")));
}

TEST_F(SourceListDirectiveTest, BasicMatchingStrictDynamic) {
  String sources = "'strict-dynamic'";
  SourceListDirective sourceList("script-src", sources, csp.get());

  EXPECT_TRUE(sourceList.allowDynamic());
}

TEST_F(SourceListDirectiveTest, BasicMatchingUnsafeHashedAttributes) {
  String sources = "'unsafe-hashed-attributes'";
  SourceListDirective sourceList("script-src", sources, csp.get());

  EXPECT_TRUE(sourceList.allowHashedAttributes());
}

TEST_F(SourceListDirectiveTest, BasicMatchingStar) {
  KURL base;
  String sources = "*";
  SourceListDirective sourceList("script-src", sources, csp.get());

  EXPECT_TRUE(sourceList.allows(KURL(base, "http://example.com/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "https://example.com/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "http://example.com/bar")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "http://foo.example.com/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "http://foo.example.com/bar")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "ftp://example.com/")));

  EXPECT_FALSE(sourceList.allows(KURL(base, "data:https://example.test/")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "blob:https://example.test/")));
  EXPECT_FALSE(
      sourceList.allows(KURL(base, "filesystem:https://example.test/")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "file:///etc/hosts")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "applewebdata://example.test/")));
}

TEST_F(SourceListDirectiveTest, StarallowsSelf) {
  KURL base;
  String sources = "*";
  SourceListDirective sourceList("script-src", sources, csp.get());

  // With a protocol of 'file', '*' allows 'file:':
  RefPtr<SecurityOrigin> origin = SecurityOrigin::create("file", "", 0);
  csp->setupSelf(*origin);
  EXPECT_TRUE(sourceList.allows(KURL(base, "file:///etc/hosts")));

  // The other results are the same as above:
  EXPECT_TRUE(sourceList.allows(KURL(base, "http://example.com/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "https://example.com/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "http://example.com/bar")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "http://foo.example.com/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "http://foo.example.com/bar")));

  EXPECT_FALSE(sourceList.allows(KURL(base, "data:https://example.test/")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "blob:https://example.test/")));
  EXPECT_FALSE(
      sourceList.allows(KURL(base, "filesystem:https://example.test/")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "applewebdata://example.test/")));
}

TEST_F(SourceListDirectiveTest, BasicMatchingSelf) {
  KURL base;
  String sources = "'self'";
  SourceListDirective sourceList("script-src", sources, csp.get());

  EXPECT_FALSE(sourceList.allows(KURL(base, "http://example.com/")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "https://not-example.com/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "https://example.test/")));
}

TEST_F(SourceListDirectiveTest, BlobMatchingSelf) {
  KURL base;
  String sources = "'self'";
  SourceListDirective sourceList("script-src", sources, csp.get());

  EXPECT_TRUE(sourceList.allows(KURL(base, "https://example.test/")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "blob:https://example.test/")));

  // Register "https" as bypassing CSP, which should trigger the innerURL
  // behavior.
  SchemeRegistry::registerURLSchemeAsBypassingContentSecurityPolicy("https");

  EXPECT_TRUE(sourceList.allows(KURL(base, "https://example.test/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "blob:https://example.test/")));

  // Unregister the scheme to clean up after ourselves.
  SchemeRegistry::removeURLSchemeRegisteredAsBypassingContentSecurityPolicy(
      "https");
}

TEST_F(SourceListDirectiveTest, BlobMatchingBlob) {
  KURL base;
  String sources = "blob:";
  SourceListDirective sourceList("script-src", sources, csp.get());

  EXPECT_FALSE(sourceList.allows(KURL(base, "https://example.test/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "blob:https://example.test/")));
}

TEST_F(SourceListDirectiveTest, BasicMatching) {
  KURL base;
  String sources = "http://example1.com:8000/foo/ https://example2.com/";
  SourceListDirective sourceList("script-src", sources, csp.get());

  EXPECT_TRUE(sourceList.allows(KURL(base, "http://example1.com:8000/foo/")));
  EXPECT_TRUE(
      sourceList.allows(KURL(base, "http://example1.com:8000/foo/bar")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "https://example2.com/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "https://example2.com/foo/")));

  EXPECT_FALSE(sourceList.allows(KURL(base, "https://not-example.com/")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "http://example1.com/")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "https://example1.com/foo")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "http://example1.com:9000/foo/")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "http://example1.com:8000/FOO/")));
}

TEST_F(SourceListDirectiveTest, WildcardMatching) {
  KURL base;
  String sources =
      "http://example1.com:*/foo/ https://*.example2.com/bar/ http://*.test/";
  SourceListDirective sourceList("script-src", sources, csp.get());

  EXPECT_TRUE(sourceList.allows(KURL(base, "http://example1.com/foo/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "http://example1.com:8000/foo/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "http://example1.com:9000/foo/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "https://foo.example2.com/bar/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "http://foo.test/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "http://foo.bar.test/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "https://example1.com/foo/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "https://example1.com:8000/foo/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "https://example1.com:9000/foo/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "https://foo.test/")));
  EXPECT_TRUE(sourceList.allows(KURL(base, "https://foo.bar.test/")));

  EXPECT_FALSE(sourceList.allows(KURL(base, "https://example1.com:8000/foo")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "https://example2.com:8000/bar")));
  EXPECT_FALSE(
      sourceList.allows(KURL(base, "https://foo.example2.com:8000/bar")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "https://example2.foo.com/bar")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "http://foo.test.bar/")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "https://example2.com/bar/")));
  EXPECT_FALSE(sourceList.allows(KURL(base, "http://test/")));
}

TEST_F(SourceListDirectiveTest, RedirectMatching) {
  KURL base;
  String sources = "http://example1.com/foo/ http://example2.com/bar/";
  SourceListDirective sourceList("script-src", sources, csp.get());

  EXPECT_TRUE(
      sourceList.allows(KURL(base, "http://example1.com/foo/"),
                        ResourceRequest::RedirectStatus::FollowedRedirect));
  EXPECT_TRUE(
      sourceList.allows(KURL(base, "http://example1.com/bar/"),
                        ResourceRequest::RedirectStatus::FollowedRedirect));
  EXPECT_TRUE(
      sourceList.allows(KURL(base, "http://example2.com/bar/"),
                        ResourceRequest::RedirectStatus::FollowedRedirect));
  EXPECT_TRUE(
      sourceList.allows(KURL(base, "http://example2.com/foo/"),
                        ResourceRequest::RedirectStatus::FollowedRedirect));
  EXPECT_TRUE(
      sourceList.allows(KURL(base, "https://example1.com/foo/"),
                        ResourceRequest::RedirectStatus::FollowedRedirect));
  EXPECT_TRUE(
      sourceList.allows(KURL(base, "https://example1.com/bar/"),
                        ResourceRequest::RedirectStatus::FollowedRedirect));

  EXPECT_FALSE(
      sourceList.allows(KURL(base, "http://example3.com/foo/"),
                        ResourceRequest::RedirectStatus::FollowedRedirect));
}

}  // namespace blink