#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include "parser/obj_parser.h"

namespace {
static std::filesystem::path WriteTempObj(const std::string& content) {
  const auto dir = std::filesystem::temp_directory_path();
  const auto ts =
      std::chrono::high_resolution_clock::now().time_since_epoch().count();
  const auto path = dir / ("obj_parser_test_" + std::to_string(ts) + ".obj");

  std::ofstream f(path, std::ios::binary);
  f << content;
  f.close();
  return path;
}

// -------------------------
// Generic accessors for Vertex
// Supports:
//  - v.x/v.y/v.z
//  - v[0]/v[1]/v[2]
//  - std::get<0/1/2>(v)
// -------------------------
template <class V>
double VX(const V& v) {
  if constexpr (requires { v.x; })
    return static_cast<double>(v.x);
  else if constexpr (requires { v[0]; })
    return static_cast<double>(v[0]);
  else if constexpr (requires { std::get<0>(v); })
    return static_cast<double>(std::get<0>(v));
  else
    static_assert(sizeof(V) == 0,
                  "Unsupported Vertex representation: cannot read X");
}

template <class V>
double VY(const V& v) {
  if constexpr (requires { v.y; })
    return static_cast<double>(v.y);
  else if constexpr (requires { v[1]; })
    return static_cast<double>(v[1]);
  else if constexpr (requires { std::get<1>(v); })
    return static_cast<double>(std::get<1>(v));
  else
    static_assert(sizeof(V) == 0,
                  "Unsupported Vertex representation: cannot read Y");
}

template <class V>
double VZ(const V& v) {
  if constexpr (requires { v.z; })
    return static_cast<double>(v.z);
  else if constexpr (requires { v[2]; })
    return static_cast<double>(v[2]);
  else if constexpr (requires { std::get<2>(v); })
    return static_cast<double>(std::get<2>(v));
  else
    static_assert(sizeof(V) == 0,
                  "Unsupported Vertex representation: cannot read Z");
}

// -------------------------
// Generic accessors for Edge
// Supports:
//  - e.first/e.second  (std::pair)
//  - e.v1/e.v2
//  - e[0]/e[1]
//  - std::get<0/1>(e)
// -------------------------
template <class E>
std::uint32_t EA(const E& e) {
  if constexpr (requires { e.first; })
    return static_cast<std::uint32_t>(e.first);
  else if constexpr (requires { e.v1; })
    return static_cast<std::uint32_t>(e.v1);
  else if constexpr (requires { e[0]; })
    return static_cast<std::uint32_t>(e[0]);
  else if constexpr (requires { std::get<0>(e); })
    return static_cast<std::uint32_t>(std::get<0>(e));
  else
    static_assert(sizeof(E) == 0,
                  "Unsupported Edge representation: cannot read endpoint A");
}

template <class E>
std::uint32_t EB(const E& e) {
  if constexpr (requires { e.second; })
    return static_cast<std::uint32_t>(e.second);
  else if constexpr (requires { e.v2; })
    return static_cast<std::uint32_t>(e.v2);
  else if constexpr (requires { e[1]; })
    return static_cast<std::uint32_t>(e[1]);
  else if constexpr (requires { std::get<1>(e); })
    return static_cast<std::uint32_t>(std::get<1>(e));
  else
    static_assert(sizeof(E) == 0,
                  "Unsupported Edge representation: cannot read endpoint B");
}

template <class EdgeT>
std::pair<std::uint32_t, std::uint32_t> ToPair(const EdgeT& e) {
  auto a = EA(e);
  auto b = EB(e);
  if (a > b) std::swap(a, b);
  return {a, b};
}

template <class EdgeT>
std::vector<std::pair<std::uint32_t, std::uint32_t>> ToPairsSorted(
    const std::vector<EdgeT>& edges) {
  std::vector<std::pair<std::uint32_t, std::uint32_t>> out;
  out.reserve(edges.size());
  for (const auto& e : edges) out.push_back(ToPair(e));
  std::sort(out.begin(), out.end());
  return out;
}

}  // namespace

TEST(ObjParser, MissingFile_ReturnsFalse_AndDoesNotModifyVectors) {
  s21::ObjParser p;

  std::vector<s21::Vertex> vertices = {s21::Vertex{1.0, 2.0, 3.0}};
  std::vector<s21::Edge> edges;
  edges.emplace_back(0u, 1u);
  std::vector<std::uint32_t> tri = {0, 1, 2};

  const bool ok =
      p.Parse("/this/path/should/not/exist.obj", vertices, edges, tri);
  EXPECT_FALSE(ok);

  // По вашему коду: при !is_open() — ранний return false без clear().
  ASSERT_EQ(vertices.size(), 1u);
  EXPECT_NEAR(VX(vertices[0]), 1.0, 1e-12);
  EXPECT_NEAR(VY(vertices[0]), 2.0, 1e-12);
  EXPECT_NEAR(VZ(vertices[0]), 3.0, 1e-12);

  ASSERT_EQ(edges.size(), 1u);
  EXPECT_EQ(ToPair(edges[0]), (std::pair<std::uint32_t, std::uint32_t>{0, 1}));

  EXPECT_EQ(tri, (std::vector<std::uint32_t>{0, 1, 2}));
}

TEST(ObjParser, EmptyFile_ReturnsTrue_AndClearsVectors) {
  const auto path = WriteTempObj("");

  s21::ObjParser p;

  std::vector<s21::Vertex> vertices = {s21::Vertex{1.0, 2.0, 3.0}};
  std::vector<s21::Edge> edges;
  edges.emplace_back(0u, 1u);
  std::vector<std::uint32_t> tri = {0, 1, 2};

  ASSERT_TRUE(p.Parse(path.string(), vertices, edges, tri));

  EXPECT_TRUE(vertices.empty());
  EXPECT_TRUE(edges.empty());
  EXPECT_TRUE(tri.empty());
}

TEST(ObjParser, VertexParsing_SkipsInvalidAndIgnoresVtVn) {
  const auto path = WriteTempObj(
      "# comment\n"
      "vt 0.1 0.2\n"
      "vn 0 0 1\n"
      "v 1 2 3\n"
      "v a b c\n"  // invalid -> skipped
      "v 4 5\n"    // invalid -> skipped (не хватает координат)
      "v   -1.5   0.25   10.0\n");

  s21::ObjParser p;
  std::vector<s21::Vertex> vertices;
  std::vector<s21::Edge> edges;
  std::vector<std::uint32_t> tri;

  ASSERT_TRUE(p.Parse(path.string(), vertices, edges, tri));
  ASSERT_EQ(vertices.size(), 2u);

  EXPECT_NEAR(VX(vertices[0]), 1.0, 1e-12);
  EXPECT_NEAR(VY(vertices[0]), 2.0, 1e-12);
  EXPECT_NEAR(VZ(vertices[0]), 3.0, 1e-12);

  EXPECT_NEAR(VX(vertices[1]), -1.5, 1e-12);
  EXPECT_NEAR(VY(vertices[1]), 0.25, 1e-12);
  EXPECT_NEAR(VZ(vertices[1]), 10.0, 1e-12);

  EXPECT_TRUE(edges.empty());
  EXPECT_TRUE(tri.empty());
}

TEST(ObjParser, TriangleFace_BuildsEdgesAndTriIndices) {
  const auto path = WriteTempObj(
      "v 0 0 0\n"
      "v 1 0 0\n"
      "v 0 1 0\n"
      "f 1 2 3\n");

  s21::ObjParser p;
  std::vector<s21::Vertex> vertices;
  std::vector<s21::Edge> edges;
  std::vector<std::uint32_t> tri;

  ASSERT_TRUE(p.Parse(path.string(), vertices, edges, tri));

  ASSERT_EQ(vertices.size(), 3u);
  ASSERT_EQ(edges.size(), 3u);
  ASSERT_EQ(tri.size(), 3u);

  const auto got = ToPairsSorted(edges);
  const std::vector<std::pair<std::uint32_t, std::uint32_t>> expected = {
      {0, 1}, {0, 2}, {1, 2}};
  EXPECT_EQ(got, expected);

  EXPECT_EQ(tri, (std::vector<std::uint32_t>{0, 1, 2}));
}

TEST(ObjParser, QuadFace_TriangulatesAsFan_AndContourEdges) {
  const auto path = WriteTempObj(
      "v 0 0 0\n"
      "v 1 0 0\n"
      "v 1 1 0\n"
      "v 0 1 0\n"
      "f 1 2 3 4\n");

  s21::ObjParser p;
  std::vector<s21::Vertex> vertices;
  std::vector<s21::Edge> edges;
  std::vector<std::uint32_t> tri;

  ASSERT_TRUE(p.Parse(path.string(), vertices, edges, tri));

  ASSERT_EQ(vertices.size(), 4u);

  const auto got = ToPairsSorted(edges);
  const std::vector<std::pair<std::uint32_t, std::uint32_t>> expected_edges = {
      {0, 1}, {0, 3}, {1, 2}, {2, 3}};
  EXPECT_EQ(got, expected_edges);

  const std::vector<std::uint32_t> expected_tri = {0, 1, 2, 0, 2, 3};
  EXPECT_EQ(tri, expected_tri);
}

TEST(ObjParser, FaceWithSlashes_ParsesOnlyVertexIndexPart) {
  const auto path = WriteTempObj(
      "v 0 0 0\n"
      "v 1 0 0\n"
      "v 0 1 0\n"
      "f 1/10/20 2/11/21 3/12/22\n");

  s21::ObjParser p;
  std::vector<s21::Vertex> vertices;
  std::vector<s21::Edge> edges;
  std::vector<std::uint32_t> tri;

  ASSERT_TRUE(p.Parse(path.string(), vertices, edges, tri));

  const auto got = ToPairsSorted(edges);
  const std::vector<std::pair<std::uint32_t, std::uint32_t>> expected = {
      {0, 1}, {0, 2}, {1, 2}};
  EXPECT_EQ(got, expected);
  EXPECT_EQ(tri, (std::vector<std::uint32_t>{0, 1, 2}));
}

TEST(ObjParser, InlineCommentInFace_IsHandled) {
  const auto path = WriteTempObj(
      "v 0 0 0\n"
      "v 1 0 0\n"
      "v 0 1 0\n"
      "f 1 2 3 # trailing comment\n");

  s21::ObjParser p;
  std::vector<s21::Vertex> vertices;
  std::vector<s21::Edge> edges;
  std::vector<std::uint32_t> tri;

  ASSERT_TRUE(p.Parse(path.string(), vertices, edges, tri));

  const auto got = ToPairsSorted(edges);
  const std::vector<std::pair<std::uint32_t, std::uint32_t>> expected = {
      {0, 1}, {0, 2}, {1, 2}};
  EXPECT_EQ(got, expected);
  EXPECT_EQ(tri, (std::vector<std::uint32_t>{0, 1, 2}));
}

TEST(ObjParser, NegativeIndices_AreSupported) {
  const auto path = WriteTempObj(
      "v 0 0 0\n"
      "v 1 0 0\n"
      "v 0 1 0\n"
      "f -3 -2 -1\n");

  s21::ObjParser p;
  std::vector<s21::Vertex> vertices;
  std::vector<s21::Edge> edges;
  std::vector<std::uint32_t> tri;

  ASSERT_TRUE(p.Parse(path.string(), vertices, edges, tri));

  const auto got = ToPairsSorted(edges);
  const std::vector<std::pair<std::uint32_t, std::uint32_t>> expected = {
      {0, 1}, {0, 2}, {1, 2}};
  EXPECT_EQ(got, expected);
  EXPECT_EQ(tri, (std::vector<std::uint32_t>{0, 1, 2}));
}

TEST(ObjParser, OutOfRangeFace_IsSkipped_ButFollowingValidFaceIsParsed) {
  const auto path = WriteTempObj(
      "v 0 0 0\n"
      "v 1 0 0\n"
      "v 0 1 0\n"
      "f 1 2 999\n"  // bad_face -> skipped
      "f 1 2 3\n"    // ok
  );

  s21::ObjParser p;
  std::vector<s21::Vertex> vertices;
  std::vector<s21::Edge> edges;
  std::vector<std::uint32_t> tri;

  ASSERT_TRUE(p.Parse(path.string(), vertices, edges, tri));

  const auto got = ToPairsSorted(edges);
  const std::vector<std::pair<std::uint32_t, std::uint32_t>> expected = {
      {0, 1}, {0, 2}, {1, 2}};
  EXPECT_EQ(got, expected);
  EXPECT_EQ(tri, (std::vector<std::uint32_t>{0, 1, 2}));
}

TEST(ObjParser, DuplicateEdges_AreRemovedBySortUnique) {
  const auto path = WriteTempObj(
      "v 0 0 0\n"
      "v 1 0 0\n"
      "v 0 1 0\n"
      "v 1 1 0\n"
      "f 1 2 3\n"
      "f 2 4 3\n");

  s21::ObjParser p;
  std::vector<s21::Vertex> vertices;
  std::vector<s21::Edge> edges;
  std::vector<std::uint32_t> tri;

  ASSERT_TRUE(p.Parse(path.string(), vertices, edges, tri));

  // Проверка отсутствия дубликатов после unique:
  auto pairs = ToPairsSorted(edges);
  EXPECT_TRUE(std::adjacent_find(pairs.begin(), pairs.end()) == pairs.end());
}