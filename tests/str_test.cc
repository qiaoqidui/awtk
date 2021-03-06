﻿#include "base/str.h"
#include "gtest/gtest.h"
#include <string>

using std::string;

TEST(Str, basic) {
  str_t str;
  str_t* s = NULL;
  s = str_init(&str, 0);

  ASSERT_EQ(s->size, 0);

  ASSERT_EQ(str_set(s, "hello"), RET_OK);
  ASSERT_EQ(str_eq(s, "hello"), TRUE);

  ASSERT_EQ(str_append(s, " world"), RET_OK);
  ASSERT_EQ(str_eq(s, "hello world"), TRUE);

  ASSERT_EQ(str_to_upper(s), RET_OK);
  ASSERT_EQ(str_eq(s, "HELLO WORLD"), TRUE);

  ASSERT_EQ(str_to_lower(s), RET_OK);
  ASSERT_EQ(str_eq(s, "hello world"), TRUE);

  ASSERT_EQ(str_replace(s, "o", "ooo"), RET_OK);
  ASSERT_EQ(str_eq(s, "hellooo wooorld"), TRUE);

  ASSERT_EQ(str_replace(s, "ooo", "xxx"), RET_OK);
  ASSERT_EQ(str_eq(s, "hellxxx wxxxrld"), TRUE);

  ASSERT_EQ(str_trim_left(s, "hel"), RET_OK);
  ASSERT_EQ(str_eq(s, "xxx wxxxrld"), TRUE);

  ASSERT_EQ(str_trim_right(s, "rld"), RET_OK);
  ASSERT_EQ(str_eq(s, "xxx wxxx"), TRUE);

  ASSERT_EQ(str_trim(s, "x "), RET_OK);
  ASSERT_EQ(str_eq(s, "w"), TRUE);

  ASSERT_EQ(str_trim_right(s, "w"), RET_OK);
  ASSERT_EQ(str_eq(s, ""), TRUE);

  ASSERT_EQ(str_set(s, "test.png"), RET_OK);
  ASSERT_EQ(str_start_with(s, "test"), TRUE);
  ASSERT_EQ(str_end_with(s, ".png"), TRUE);

  str_reset(s);
}

TEST(Str, set_with_len) {
  str_t str;
  str_t* s = NULL;
  s = str_init(&str, 0);

  ASSERT_EQ(str_set_with_len(s, "hello world", 0), RET_OK);
  ASSERT_EQ(str_eq(s, ""), TRUE);

  ASSERT_EQ(str_set_with_len(s, "hello world", 1), RET_OK);
  ASSERT_EQ(str_eq(s, "h"), TRUE);

  ASSERT_EQ(str_set_with_len(s, "hello world", 5), RET_OK);
  ASSERT_EQ(str_eq(s, "hello"), TRUE);

  str_reset(s);
}

TEST(Str, decode_xml_entity) {
  str_t str;
  str_t* s = NULL;
  s = str_init(&str, 0);

  ASSERT_EQ(str_decode_xml_entity(s, "a&lt;b"), RET_OK);
  ASSERT_EQ(str_eq(s, "a<b"), TRUE);

  ASSERT_EQ(str_decode_xml_entity(s, "a&lt;b&gt;c"), RET_OK);
  ASSERT_EQ(str_eq(s, "a<b>c"), TRUE);

  ASSERT_EQ(str_decode_xml_entity(s, "&quota;a&lt;b&gt;c&quota;"), RET_OK);
  ASSERT_EQ(str_eq(s, "\"a<b>c\""), TRUE);

  ASSERT_EQ(str_decode_xml_entity(s, "&quota;a&lt;b&gt;c&quota;&amp;&amp;"), RET_OK);
  ASSERT_EQ(str_eq(s, "\"a<b>c\"&&"), TRUE);

  str_reset(s);
}

TEST(Str, value) {
  str_t str;
  value_t v;
  str_t* s = str_init(&str, 0);

  value_set_int(&v, 100);
  ASSERT_EQ(str_from_value(s, &v), RET_OK);
  ASSERT_EQ(string(s->str), string("100"));

  value_set_str(&v, "123");
  ASSERT_EQ(str_from_value(s, &v), RET_OK);
  ASSERT_EQ(string(s->str), string("123"));

  value_set_wstr(&v, L"abc");
  ASSERT_EQ(str_from_value(s, &v), RET_OK);
  ASSERT_EQ(string(s->str), string("abc"));

  str_reset(s);
}

TEST(Str, insert) {
  str_t str;
  str_t* s = str_init(&str, 0);

  ASSERT_EQ(str_insert(s, 0, "abc"), RET_OK);
  ASSERT_EQ(string(s->str), "abc");

  ASSERT_EQ(str_insert(s, 0, "abc"), RET_OK);
  ASSERT_EQ(string(s->str), "abcabc");

  ASSERT_EQ(str_insert(s, 1, "A"), RET_OK);
  ASSERT_EQ(string(s->str), "aAbcabc");

  ASSERT_EQ(str_insert(s, 3, "B"), RET_OK);
  ASSERT_EQ(string(s->str), "aAbBcabc");

  ASSERT_EQ(str_insert(s, 8, "C"), RET_OK);
  ASSERT_EQ(string(s->str), "aAbBcabcC");

  str_reset(s);
}

TEST(Str, remove) {
  str_t str;
  str_t* s = str_init(&str, 0);

  ASSERT_EQ(str_set(s, "abc"), RET_OK);
  ASSERT_EQ(str_remove(s, 0, 3), RET_OK);
  ASSERT_EQ(string(s->str), "");

  ASSERT_EQ(str_set(s, "abc"), RET_OK);
  ASSERT_EQ(str_remove(s, 0, 1), RET_OK);
  ASSERT_EQ(string(s->str), "bc");

  ASSERT_EQ(str_set(s, "abc"), RET_OK);
  ASSERT_EQ(str_remove(s, 1, 1), RET_OK);
  ASSERT_EQ(string(s->str), "ac");

  ASSERT_EQ(str_set(s, "abc"), RET_OK);
  ASSERT_EQ(str_remove(s, 2, 1), RET_OK);
  ASSERT_EQ(string(s->str), "ab");

  str_reset(s);
}
