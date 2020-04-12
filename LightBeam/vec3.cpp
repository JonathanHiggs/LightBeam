#include "vec3.hpp"


const Vec3 Vec3::nan = Vec3(std::nan("1"), std::nan("1"), std::nan("1"));
const Vec3 Vec3::one = Vec3(1, 1, 1);
const Vec3 Vec3::zero = Vec3(0, 0, 0);
const Vec3 Vec3::unit_x = Vec3(1, 0, 0);
const Vec3 Vec3::unit_y = Vec3(0, 1, 0);
const Vec3 Vec3::unit_z = Vec3(0, 0, 1);