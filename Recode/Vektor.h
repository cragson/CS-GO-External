#pragma once
#include <float.h>
#include <Windows.h>
#include <emmintrin.h>
#include <math.h>
#include <random>
#ifdef VECTOR_PARANOIA
#define CHECK_VALID( _v)	Assert( (_v).IsValid() )
#else
#ifdef GNUC
#define CHECK_VALID( _v)
#else
#define CHECK_VALID( _v)	0
#endif
#endif

class VectorByValue;
typedef float vec_t;


// 3D Vector
class Vector
{
public:
	// Members
	vec_t x, y, z;

	// Construction/destruction:
	Vector(void);
	Vector(vec_t X, vec_t Y, vec_t Z);
	Vector(vec_t* clr);

	// Initialization
	void Init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f);
	// TODO (Ilya): Should there be an init that takes a single float for consistency?

	// Got any nasty NAN's?
	bool IsValid() const;
	void Invalidate();

	// array access...
	vec_t operator[](int i) const;
	vec_t&operator[](int i);

	// Base address...
	vec_t*Base();
	vec_t const*Base() const;

	// Initialization methods
	void Random(vec_t minVal, vec_t maxVal);
	inline void Zero(); ///< zero out a vector

						// equality
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;

	// arithmetic operations
	Vector&operator+=(const Vector& v);
	Vector&operator-=(const Vector& v);
	Vector&operator*=(const Vector& v);
	Vector&operator*=(float s);
	Vector&operator/=(const Vector& v);
	Vector&operator/=(float s);
	Vector&operator+=(float fl); ///< broadcast add
	Vector&operator-=(float fl); ///< broadcast sub			

								 // negate the vector components
	void Negate();

	// Get the vector's magnitude.
	inline vec_t Length() const;

	// Get the vector's magnitude squared.
	vec_t LengthSqr(void) const
	{
		CHECK_VALID(*this);
		return (x * x + y * y + z * z);
	}


	Vector Vector::Clamp()
	{
		if (y < -180.0f)
			y += 360.0f;
		if (y > 180.0f)
			y -= 360.0f;

		if (x < -89.0f)
			x = -89.0f;
		if (x > 89.0f)
			x = 89.0f;

		return *this;
	}

	// return true if this vector is (0,0,0) within tolerance
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}


	vec_t NormalizeInPlace();
	Vector Normalized() const;
	bool IsLengthGreaterThan(float val) const;
	bool IsLengthLessThan(float val) const;


	// Get the distance from this vector to the other one.
	vec_t DistTo(const Vector& vOther) const;

	// Get the distance from this vector to the other one squared.
	// NJS: note, VC wasn't inlining it correctly in several deeply nested inlines due to being an 'out of line' inline.  
	// may be able to tidy this up after switching to VC7
	vec_t DistToSqr(const Vector& vOther) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.LengthSqr();
	}

	// Copy
	void CopyToArray(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual vector equation (because it's done per-component
	// rather than per-vector).
	void MulAdd(const Vector& a, const Vector& b, float scalar);

	// Dot product.
	vec_t Dot(const Vector& vOther) const;

	// assignment
	Vector&operator=(const Vector& vOther);

	// returns 0, 1, 2 corresponding to the component with the largest absolute value
	inline int LargestComponent() const;

	// 2d
	vec_t Length2D(void) const;
	vec_t Length2DSqr(void) const;

	/// get the component of this vector parallel to some other given vector
	inline Vector ProjectOnto(const Vector& onto);

	operator VectorByValue &() { return *((VectorByValue *)(this)); }
	operator const VectorByValue &() const { return *((const VectorByValue *)(this)); }

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// copy constructors
	//	Vector(const Vector &vOther);

	// arithmetic operations
	Vector operator-(void) const;

	Vector operator+(const Vector& v) const;
	Vector operator-(const Vector& v) const;
	Vector operator*(const Vector& v) const;
	Vector operator/(const Vector& v) const;
	Vector operator*(float fl) const;
	Vector operator/(float fl) const;

	// Cross product between two vectors.
	Vector Cross(const Vector& vOther) const;

	// Returns a vector with the min or max in X, Y, and Z.
	Vector Min(const Vector& vOther) const;
	Vector Max(const Vector& vOther) const;


#else

private:
	// No copy constructors allowed if we're in optimal mode
	Vector(const Vector& vOther);
#endif
};

typedef Vector QAngle;

#define USE_M64S ( ( !defined( _X360 ) ) )


//=========================================================
// 4D Integer Vector
//=========================================================
class IntVector4D
{
public:

	int x, y, z, w;

	// Initialization
	void Init(int ix = 0, int iy = 0, int iz = 0, int iw = 0);


	// Setter
	void Set(const IntVector4D& vOther);
	void Set(const int ix, const int iy, const int iz, const int iw);

	// array access...
	int operator[](int i) const;
	int&operator[](int i);

	// Base address...
	int*Base();
	int const*Base() const;

	// equality
	bool operator==(const IntVector4D& v) const;
	bool operator!=(const IntVector4D& v) const;

	// Arithmetic operations
	IntVector4D&operator+=(const IntVector4D& v);
	IntVector4D&operator-=(const IntVector4D& v);
	IntVector4D&operator*=(const IntVector4D& v);
	IntVector4D&operator*=(float s);
	IntVector4D&operator/=(const IntVector4D& v);
	IntVector4D&operator/=(float s);
	IntVector4D operator*(float fl) const;

private:

	// No copy constructors allowed if we're in optimal mode
	//	IntVector4D(IntVector4D const& vOther);

	// No assignment operators either...
	//	IntVector4D& operator=( IntVector4D const& src );
};


//-----------------------------------------------------------------------------
// Allows us to specifically pass the vector by value when we need to
//-----------------------------------------------------------------------------
class VectorByValue : public Vector
{
public:
	// Construction/destruction:
	VectorByValue(void) : Vector() { }

	VectorByValue(vec_t X, vec_t Y, vec_t Z) : Vector(X, Y, Z) { }

	VectorByValue(const VectorByValue& vOther) { *this = vOther; }
};


//-----------------------------------------------------------------------------
// Utility to simplify table construction. No constructor means can use
// traditional C-style initialization
//-----------------------------------------------------------------------------
class TableVector
{
public:
	vec_t x, y, z;

	operator Vector &() { return *((Vector *)(this)); }
	operator const Vector &() const { return *((const Vector *)(this)); }

	// array access...
	vec_t&operator[](int i)
	{
		return ((vec_t*)this)[i];
	}

	vec_t operator[](int i) const
	{
		return ((vec_t*)this)[i];
	}
};


//-----------------------------------------------------------------------------
// Here's where we add all those lovely SSE optimized routines
//-----------------------------------------------------------------------------

class VectorAligned : public Vector
{
public:
	VectorAligned(void) { };

	VectorAligned(vec_t X, vec_t Y, vec_t Z)
	{
		Init(X, Y, Z);
	}

#ifdef VECTOR_NO_SLOW_OPERATIONS

private:
	// No copy constructors allowed if we're in optimal mode
	VectorAligned(const VectorAligned& vOther);
	VectorAligned(const Vector &vOther);

#else
public:
	explicit VectorAligned(const Vector& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
	}

	VectorAligned&operator=(const Vector& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	VectorAligned&operator=(const VectorAligned& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
		return *this;
	}


#endif
	float w; // this space is used anyway
};

//-----------------------------------------------------------------------------
// Vector related operations
//-----------------------------------------------------------------------------

// Vector clear
FORCEINLINE void VectorClear(Vector& a);

// Copy
FORCEINLINE void VectorCopy(const Vector& src, Vector& dst);

// Vector arithmetic
FORCEINLINE void VectorAdd(const Vector& a, const Vector& b, Vector& result);
FORCEINLINE void VectorSubtract(const Vector& a, const Vector& b, Vector& result);
FORCEINLINE void VectorMultiply(const Vector& a, vec_t b, Vector& result);
FORCEINLINE void VectorMultiply(const Vector& a, const Vector& b, Vector& result);
FORCEINLINE void VectorDivide(const Vector& a, vec_t b, Vector& result);
FORCEINLINE void VectorDivide(const Vector& a, const Vector& b, Vector& result);
inline void VectorScale(const Vector& in, vec_t scale, Vector& result);
inline void VectorMA(const Vector& start, float scale, const Vector& direction, Vector& dest);

// Vector equality with tolerance
bool VectorsAreEqual(const Vector& src1, const Vector& src2, float tolerance = 0.0f);

#define VectorExpand(v) (v).x, (v).y, (v).z


// Normalization
// FIXME: Can't use quite yet
//vec_t VectorNormalize( Vector& v );

// Length
inline vec_t VectorLength(const Vector& v);

// Dot Product
FORCEINLINE vec_t DotProduct(const Vector& a, const Vector& b);

// Cross product
void CrossProduct(const Vector& a, const Vector& b, Vector& result);

// Store the min or max of each of x, y, and z into the result.
void VectorMin(const Vector& a, const Vector& b, Vector& result);
void VectorMax(const Vector& a, const Vector& b, Vector& result);

// Linearly interpolate between two vectors
void VectorLerp(const Vector& src1, const Vector& src2, vec_t t, Vector& dest);
Vector VectorLerp(const Vector& src1, const Vector& src2, vec_t t);

FORCEINLINE Vector ReplicateToVector(float x)
{
	return Vector(x, x, x);
}

// check if a point is in the field of a view of an object.
FORCEINLINE bool PointWithinViewAngle(Vector const& vecSrcPosition,
	Vector const& vecTargetPosition,
	Vector const& vecLookDirection, float flCosHalfFOV)
{
	Vector vecDelta = vecTargetPosition - vecSrcPosition;
	float cosDiff = DotProduct(vecLookDirection, vecDelta);

	if (flCosHalfFOV <= 0) // >180
	{
		// signs are different, answer is implicit
		if (cosDiff > 0)
			return true;

		// a/sqrt(b) > c  == a^2 < b * c ^2
		// IFF left and right sides are <= 0
		float flLen2 = vecDelta.LengthSqr();
		return (cosDiff * cosDiff <= flLen2 * flCosHalfFOV * flCosHalfFOV);
	}
	// flCosHalfFOV > 0
	// signs are different, answer is implicit
	if (cosDiff < 0)
		return false;

	// a/sqrt(b) > c  == a^2 > b * c ^2
	// IFF left and right sides are >= 0
	float flLen2 = vecDelta.LengthSqr();
	return (cosDiff * cosDiff >= flLen2 * flCosHalfFOV * flCosHalfFOV);
}


#ifndef VECTOR_NO_SLOW_OPERATIONS

// Cross product
Vector CrossProduct(const Vector& a, const Vector& b);

// Random vector creation
Vector RandomVector(vec_t minVal, vec_t maxVal);

#endif

float RandomVectorInUnitSphere(Vector* pVector);


//-----------------------------------------------------------------------------
//
// Inlined Vector methods
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------
inline Vector::Vector(void)
{
#ifdef _DEBUG
#ifdef VECTOR_PARANOIA
	// Initialize to NAN to catch errors
	x = y = z = VEC_T_NAN;
#endif
#endif
}

inline Vector::Vector(vec_t X, vec_t Y, vec_t Z)
{
	x = X;
	y = Y;
	z = Z;
	CHECK_VALID(*this);
}

inline Vector::Vector(vec_t* clr)
{
	if (clr) {
		x = clr[0];
		y = clr[1];
		z = clr[2];
		CHECK_VALID(*this);
	}
}

//inline Vector::Vector(const float *pFloat)					
//{
//	Assert( pFloat );
//	x = pFloat[0]; y = pFloat[1]; z = pFloat[2];	
//	CHECK_VALID(*this);
//} 

#if 0
//-----------------------------------------------------------------------------
// copy constructor
//-----------------------------------------------------------------------------

inline Vector::Vector(const Vector &vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x; y = vOther.y; z = vOther.z;
}
#endif

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

inline void Vector::Init(vec_t ix, vec_t iy, vec_t iz)
{
	x = ix;
	y = iy;
	z = iz;
	CHECK_VALID(*this);
}

inline void Vector::Random(vec_t minVal, vec_t maxVal)
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	CHECK_VALID(*this);
}

// This should really be a single opcode on the PowerPC (move r0 onto the vec reg)
inline void Vector::Zero()
{
	x = y = z = 0.0f;
}

inline void VectorClear(Vector& a)
{
	a.x = a.y = a.z = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

inline Vector&Vector::operator=(const Vector& vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x;
	y = vOther.y;
	z = vOther.z;
	return *this;
}


//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
inline vec_t&Vector::operator[](int i)
{
	return ((vec_t*)this)[i];
}

inline vec_t Vector::operator[](int i) const
{
	return ((vec_t*)this)[i];
}


//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline vec_t*Vector::Base()
{
	return (vec_t*)this;
}

inline vec_t const*Vector::Base() const
{
	return (vec_t const*)this;
}


//-----------------------------------------------------------------------------
// Invalidate
//-----------------------------------------------------------------------------

inline void Vector::Invalidate()
{
	//#ifdef _DEBUG
	//#ifdef VECTOR_PARANOIA
	x = y = z = 0;
	//#endif
	//#endif
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

inline bool Vector::operator==(const Vector& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y) && (src.z == z);
}

inline bool Vector::operator!=(const Vector& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y) || (src.z != z);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

FORCEINLINE void VectorCopy(const Vector& src, Vector& dst)
{
	CHECK_VALID(src);
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}

inline void Vector::CopyToArray(float* rgfl) const
{
	CHECK_VALID(*this);
	rgfl[0] = x, rgfl[1] = y, rgfl[2] = z;
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------
// #pragma message("TODO: these should be SSE")

inline void Vector::Negate()
{
	CHECK_VALID(*this);
	x = -x;
	y = -y;
	z = -z;
}

FORCEINLINE Vector&Vector::operator+=(const Vector& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

FORCEINLINE Vector&Vector::operator-=(const Vector& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

FORCEINLINE Vector&Vector::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	CHECK_VALID(*this);
	return *this;
}

FORCEINLINE Vector&Vector::operator*=(const Vector& v)
{
	CHECK_VALID(v);
	x *= v.x;
	y *= v.y;
	z *= v.z;
	CHECK_VALID(*this);
	return *this;
}

// this ought to be an opcode.
FORCEINLINE Vector&Vector::operator+=(float fl)
{
	x += fl;
	y += fl;
	z += fl;
	CHECK_VALID(*this);
	return *this;
}

FORCEINLINE Vector&Vector::operator-=(float fl)
{
	x -= fl;
	y -= fl;
	z -= fl;
	CHECK_VALID(*this);
	return *this;
}


FORCEINLINE Vector&Vector::operator/=(float fl)
{
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	CHECK_VALID(*this);
	return *this;
}

FORCEINLINE Vector&Vector::operator/=(const Vector& v)
{
	CHECK_VALID(v);

	x /= v.x;
	y /= v.y;
	z /= v.z;
	CHECK_VALID(*this);
	return *this;
}


// get the component of this vector parallel to some other given vector
inline Vector Vector::ProjectOnto(const Vector& onto)
{
	return onto * (this->Dot(onto) / (onto.LengthSqr()));
}


//-----------------------------------------------------------------------------
//
// Inlined Integer Vector methods
//
//-----------------------------------------------------------------------------


inline void IntVector4D::Init(int ix, int iy, int iz, int iw)
{
	x = ix;
	y = iy;
	z = iz;
	w = iw;
}

FORCEINLINE void IntVector4D::Set(const IntVector4D& vOther)
{
	x = vOther.x;
	y = vOther.y;
	z = vOther.z;
	w = vOther.w;
}

FORCEINLINE void IntVector4D::Set(const int ix, const int iy, const int iz, const int iw)
{
	x = ix;
	y = iy;
	z = iz;
	w = iw;
}


//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
inline int IntVector4D::operator[](int i) const
{
	return ((int*)this)[i];
}

inline int&IntVector4D::operator[](int i)
{
	return ((int*)this)[i];
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline int*IntVector4D::Base()
{
	return (int*)this;
}

inline int const*IntVector4D::Base() const
{
	return (int const*)this;
}


//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

inline bool IntVector4D::operator==(const IntVector4D& src) const
{
	return (src.x == x) && (src.y == y) && (src.z == z) && (src.w == w);
}

inline bool IntVector4D::operator!=(const IntVector4D& src) const
{
	return (src.x != x) || (src.y != y) || (src.z != z) || (src.w != w);
}


//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------

FORCEINLINE IntVector4D&IntVector4D::operator+=(const IntVector4D& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

FORCEINLINE IntVector4D&IntVector4D::operator-=(const IntVector4D& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

FORCEINLINE IntVector4D&IntVector4D::operator*=(float fl)
{
	x = (int)(x * fl);
	y = (int)(y * fl);
	z = (int)(z * fl);
	w = (int)(w * fl);
	return *this;
}

FORCEINLINE IntVector4D&IntVector4D::operator*=(const IntVector4D& v)
{
	x = (int)(x * v.x);
	y = (int)(y * v.y);
	z = (int)(z * v.z);
	w = (int)(w * v.w);
	return *this;
}

FORCEINLINE IntVector4D&IntVector4D::operator/=(float fl)
{
	float oofl = 1.0f / fl;
	x = (int)(x * oofl);
	y = (int)(y * oofl);
	z = (int)(z * oofl);
	w = (int)(w * oofl);
	return *this;
}

FORCEINLINE IntVector4D&IntVector4D::operator/=(const IntVector4D& v)
{
	x = (int)(x / v.x);
	y = (int)(y / v.y);
	z = (int)(z / v.z);
	w = (int)(w / v.w);
	return *this;
}

FORCEINLINE void IntVector4DMultiply(const IntVector4D& src, float fl, IntVector4D& res)
{
	res.x = (int)(src.x * fl);
	res.y = (int)(src.y * fl);
	res.z = (int)(src.z * fl);
	res.w = (int)(src.w * fl);
}

FORCEINLINE IntVector4D IntVector4D::operator*(float fl) const
{
	IntVector4D res;
	IntVector4DMultiply(*this, fl, res);
	return res;
}


// =======================


FORCEINLINE void VectorAdd(const Vector& a, const Vector& b, Vector& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

FORCEINLINE void VectorSubtract(const Vector& a, const Vector& b, Vector& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

FORCEINLINE void VectorMultiply(const Vector& a, vec_t b, Vector& c)
{
	CHECK_VALID(a);
	c.x = a.x * b;
	c.y = a.y * b;
	c.z = a.z * b;
}

FORCEINLINE void VectorMultiply(const Vector& a, const Vector& b, Vector& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
}

// for backwards compatability
inline void VectorScale(const Vector& in, vec_t scale, Vector& result)
{
	VectorMultiply(in, scale, result);
}


FORCEINLINE void VectorDivide(const Vector& a, vec_t b, Vector& c)
{
	CHECK_VALID(a);
	vec_t oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
	c.z = a.z * oob;
}

FORCEINLINE void VectorDivide(const Vector& a, const Vector& b, Vector& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);

	c.x = a.x / b.x;
	c.y = a.y / b.y;
	c.z = a.z / b.z;
}

// FIXME: Remove
// For backwards compatability
inline void Vector::MulAdd(const Vector& a, const Vector& b, float scalar)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
	z = a.z + b.z * scalar;
}

inline void VectorLerp(const Vector& src1, const Vector& src2, vec_t t, Vector& dest)
{
	CHECK_VALID(src1);
	CHECK_VALID(src2);
	dest.x = src1.x + (src2.x - src1.x) * t;
	dest.y = src1.y + (src2.y - src1.y) * t;
	dest.z = src1.z + (src2.z - src1.z) * t;
}

inline Vector VectorLerp(const Vector& src1, const Vector& src2, vec_t t)
{
	Vector result;
	VectorLerp(src1, src2, t, result);
	return result;
}


inline vec_t VectorLength(const Vector& v)
{
	return (vec_t)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

//-----------------------------------------------------------------------------
// dot, cross
//-----------------------------------------------------------------------------
FORCEINLINE vec_t DotProduct(const Vector& a, const Vector& b)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// for backwards compatability
inline vec_t Vector::Dot(const Vector& vOther) const
{
	CHECK_VALID(vOther);
	return DotProduct(*this, vOther);
}

inline int Vector::LargestComponent() const
{
	float flAbsx = fabs(x);
	float flAbsy = fabs(y);
	float flAbsz = fabs(z);
	if (flAbsx > flAbsy) {
		if (flAbsx > flAbsz)
			return 0;
		return 2;
	}
	if (flAbsy > flAbsz)
		return 1;
	return 2;
}

inline void CrossProduct(const Vector& a, const Vector& b, Vector& result)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
}


inline vec_t Vector::Length(void) const
{
	CHECK_VALID(*this);
	return VectorLength(*this);
}


//-----------------------------------------------------------------------------
// Normalization
//-----------------------------------------------------------------------------

// FIXME: Can't use until we're un-macroed in mathlib.h
inline vec_t NormalizeVector(Vector& v)
{
	vec_t l = v.Length();
	if (l != 0.0f) {
		v.x = v.x / l;
		v.y = v.y / l;
		v.z = v.z / l;
	}
	else
		v.x = v.y = 0.0f;
	v.z = 1.0f;
	return l;
}

//-----------------------------------------------------------------------------
// Get the distance from this vector to the other one 
//-----------------------------------------------------------------------------
inline vec_t Vector::DistTo(const Vector& vOther) const
{
	Vector delta;
	VectorSubtract(*this, vOther, delta);
	return delta.Length();
}

//-----------------------------------------------------------------------------
// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
//-----------------------------------------------------------------------------
inline void ComputeClosestPoint(const Vector& vecStart, float flMaxDist, const Vector& vecTarget, Vector* pResult)
{
	Vector vecDelta;
	VectorSubtract(vecTarget, vecStart, vecDelta);
	float flDistSqr = vecDelta.LengthSqr();
	if (flDistSqr <= flMaxDist * flMaxDist) {
		*pResult = vecTarget;
	}
	else {
		vecDelta /= sqrt(flDistSqr);
		VectorMA(vecStart, flMaxDist, vecDelta, *pResult);
	}
}


//-----------------------------------------------------------------------------
//
// Slow methods
//
//-----------------------------------------------------------------------------

#ifndef VECTOR_NO_SLOW_OPERATIONS

//-----------------------------------------------------------------------------
// Returns a vector with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------
inline Vector Vector::Min(const Vector& vOther) const
{
	return Vector(x < vOther.x ? x : vOther.x,
		y < vOther.y ? y : vOther.y,
		z < vOther.z ? z : vOther.z);
}

inline Vector Vector::Max(const Vector& vOther) const
{
	return Vector(x > vOther.x ? x : vOther.x,
		y > vOther.y ? y : vOther.y,
		z > vOther.z ? z : vOther.z);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

inline Vector Vector::operator-(void) const
{
	return Vector(-x, -y, -z);
}

inline Vector Vector::operator+(const Vector& v) const
{
	Vector res;
	VectorAdd(*this, v, res);
	return res;
}

inline Vector Vector::operator-(const Vector& v) const
{
	Vector res;
	VectorSubtract(*this, v, res);
	return res;
}

inline Vector Vector::operator*(float fl) const
{
	Vector res;
	VectorMultiply(*this, fl, res);
	return res;
}

inline Vector Vector::operator*(const Vector& v) const
{
	Vector res;
	VectorMultiply(*this, v, res);
	return res;
}

inline Vector Vector::operator/(float fl) const
{
	Vector res;
	VectorDivide(*this, fl, res);
	return res;
}

inline Vector Vector::operator/(const Vector& v) const
{
	Vector res;
	VectorDivide(*this, v, res);
	return res;
}

inline Vector operator*(float fl, const Vector& v)
{
	return v * fl;
}

//-----------------------------------------------------------------------------
// cross product
//-----------------------------------------------------------------------------

inline Vector Vector::Cross(const Vector& vOther) const
{
	Vector res;
	CrossProduct(*this, vOther, res);
	return res;
}

//-----------------------------------------------------------------------------
// 2D
//-----------------------------------------------------------------------------

inline vec_t Vector::Length2D(void) const
{
	return (vec_t)sqrt(x * x + y * y);
}

inline vec_t Vector::Length2DSqr(void) const
{
	return (x * x + y * y);
}

inline Vector CrossProduct(const Vector& a, const Vector& b)
{
	return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}


inline float ComputeVolume(const Vector& vecMins, const Vector& vecMaxs)
{
	Vector vecDelta;
	VectorSubtract(vecMaxs, vecMins, vecDelta);
	return DotProduct(vecDelta, vecDelta);
}

// Get a random vector.
inline Vector RandomVector(float minVal, float maxVal)
{
	Vector random;
	random.Random(minVal, maxVal);
	return random;
}

#endif //slow

//-----------------------------------------------------------------------------
// Helper debugging stuff....
//-----------------------------------------------------------------------------

inline bool operator==(float const* f, const Vector& v)
{
	// AIIIEEEE!!!!Assert(0);
	return false;
}

inline bool operator==(const Vector& v, float const* f)
{
	// AIIIEEEE!!!!Assert(0);
	return false;
}

inline bool operator!=(float const* f, const Vector& v)
{
	// AIIIEEEE!!!!Assert(0);
	return false;
}

inline bool operator!=(const Vector& v, float const* f)
{
	// AIIIEEEE!!!!Assert(0);
	return false;
}


// return a vector perpendicular to another, with smooth variation. The difference between this and
// something like VectorVectors is that there are now discontinuities. _unlike_ VectorVectors,
// you won't get an "u
void VectorPerpendicularToVector(Vector const& in, Vector* pvecOut);

//-----------------------------------------------------------------------------
// AngularImpulse
//-----------------------------------------------------------------------------
// AngularImpulse are exponetial maps (an axis scaled by a "twist" angle in degrees)
typedef Vector AngularImpulse;

#ifndef VECTOR_NO_SLOW_OPERATIONS

inline AngularImpulse RandomAngularImpulse(float minVal, float maxVal)
{
	AngularImpulse angImp;
	angImp.Random(minVal, maxVal);
	return angImp;
}

#endif


//-----------------------------------------------------------------------------
// Quaternion
//-----------------------------------------------------------------------------

class RadianEuler;

class Quaternion // same data-layout as engine's vec4_t,
{ //		which is a vec_t[4]
public:
	Quaternion(void)
	{
		// Initialize to NAN to catch errors
#ifdef _DEBUG
#ifdef VECTOR_PARANOIA
		x = y = z = w = VEC_T_NAN;
#endif
#endif
	}

	Quaternion(vec_t ix, vec_t iy, vec_t iz, vec_t iw) : x(ix), y(iy), z(iz), w(iw) { }

	inline Quaternion(RadianEuler const& angle); // evil auto type promotion!!!

	void Init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f, vec_t iw = 0.0f)
	{
		x = ix;
		y = iy;
		z = iz;
		w = iw;
	}

	bool IsValid() const;
	void Invalidate();

	bool operator==(const Quaternion& src) const;
	bool operator!=(const Quaternion& src) const;

	vec_t*Base() { return (vec_t*)this; }
	const vec_t*Base() const { return (vec_t*)this; }

	// array access...
	vec_t operator[](int i) const;
	vec_t&operator[](int i);

	vec_t x, y, z, w;
};


//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
inline vec_t&Quaternion::operator[](int i)
{
	return ((vec_t*)this)[i];
}

inline vec_t Quaternion::operator[](int i) const
{
	return ((vec_t*)this)[i];
}


//-----------------------------------------------------------------------------
// Equality test
//-----------------------------------------------------------------------------
inline bool Quaternion::operator==(const Quaternion& src) const
{
	return (x == src.x) && (y == src.y) && (z == src.z) && (w == src.w);
}

inline bool Quaternion::operator!=(const Quaternion& src) const
{
	return !operator==(src);
}


//-----------------------------------------------------------------------------
// Here's where we add all those lovely SSE optimized routines
//-----------------------------------------------------------------------------
class QuaternionAligned : public Quaternion
{
public:
	QuaternionAligned(void) { };

	QuaternionAligned(vec_t X, vec_t Y, vec_t Z, vec_t W)
	{
		Init(X, Y, Z, W);
	}

	operator Quaternion *() { return this; }
	operator const Quaternion *() { return this; }

#ifdef VECTOR_NO_SLOW_OPERATIONS

private:
	// No copy constructors allowed if we're in optimal mode
	QuaternionAligned(const QuaternionAligned& vOther);
	QuaternionAligned(const Quaternion &vOther);

#else
public:
	explicit QuaternionAligned(const Quaternion& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z, vOther.w);
	}

	QuaternionAligned&operator=(const Quaternion& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z, vOther.w);
		return *this;
	}

	QuaternionAligned&operator=(const QuaternionAligned& vOther)
	{
		// we know we're aligned, so use simd
		// we can't use the convenient abstract interface coz it gets declared later
#ifdef _X360
		XMStoreVector4A(Base(), XMLoadVector4A(vOther.Base()));
#elif _WIN32
		_mm_store_ps(Base(), _mm_load_ps(vOther.Base()));
#else
		Init(vOther.x, vOther.y, vOther.z, vOther.w);
#endif
		return *this;
	}

#endif
};


class RadianEuler
{
public:
	RadianEuler(void) { }

	RadianEuler(vec_t X, vec_t Y, vec_t Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	inline RadianEuler(Quaternion const& q); // evil auto type promotion!!!
	inline RadianEuler(QAngle const& angles); // evil auto type promotion!!!

											  // Initialization
	void Init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f)
	{
		x = ix;
		y = iy;
		z = iz;
	}

	//	conversion to qangle
	QAngle ToQAngle(void) const;
	bool IsValid() const;
	void Invalidate();

	vec_t*Base() { return &x; }
	const vec_t*Base() const { return &x; }

	// array access...
	vec_t operator[](int i) const;
	vec_t&operator[](int i);

	vec_t x, y, z;
};


extern void AngleQuaternion(RadianEuler const& angles, Quaternion& qt);
extern void QuaternionAngles(Quaternion const& q, RadianEuler& angles);

inline Quaternion::Quaternion(RadianEuler const& angle)
{
	AngleQuaternion(angle, *this);
}

inline bool Quaternion::IsValid() const
{
	return true;
}

inline void Quaternion::Invalidate()
{
	//#ifdef _DEBUG
	//#ifdef VECTOR_PARANOIA
	x = y = z = w = 90;
	//#endif
	//#endif
}

inline RadianEuler::RadianEuler(Quaternion const& q)
{
	QuaternionAngles(q, *this);
}

inline void VectorCopy(RadianEuler const& src, RadianEuler& dst)
{
	CHECK_VALID(src);
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}

inline void VectorScale(RadianEuler const& src, float b, RadianEuler& dst)
{
	CHECK_VALID(src);
	dst.x = src.x * b;
	dst.y = src.y * b;
	dst.z = src.z * b;
}

inline bool RadianEuler::IsValid() const
{
	return true;
}

inline void RadianEuler::Invalidate()
{
	//#ifdef _DEBUG
	//#ifdef VECTOR_PARANOIA
	x = y = z = 9;
	//#endif
	//#endif
}


//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
inline vec_t&RadianEuler::operator[](int i)
{
	return ((vec_t*)this)[i];
}

inline vec_t RadianEuler::operator[](int i) const
{
	return ((vec_t*)this)[i];
}


// FIXME: Change this back to a #define once we get rid of the vec_t version
float NormalizeVector(Vector& v);

// FIXME: Obsolete version of VectorNormalize, once we remove all the friggin float*s
FORCEINLINE float NormalizeVector(float* v)
{
	return NormalizeVector(*(reinterpret_cast< Vector * >(v)));
}

#if defined(__i386__) || defined(_M_IX86)
inline void _SSE_RSqrtInline(float a, float* out)
{
	__m128 xx = _mm_load_ss(&a);
	__m128 xr = _mm_rsqrt_ss(xx);
	__m128 xt;
	xt = _mm_mul_ss(xr, xr);
	xt = _mm_mul_ss(xt, xx);
	xt = _mm_sub_ss(_mm_set_ss(3.f), xt);
	xt = _mm_mul_ss(xt, _mm_set_ss(0.5f));
	xr = _mm_mul_ss(xr, xt);
	_mm_store_ss(out, xr);
}
#endif
// FIXME: Change this back to a #define once we get rid of the vec_t version
FORCEINLINE float VectorNormalize(Vector& vec)
{
#ifndef DEBUG // stop crashing my edit-and-continue!
#if defined(__i386__) || defined(_M_IX86)
#define DO_SSE_OPTIMIZATION
#endif
#endif

	float sqrlen = vec.LengthSqr() + 1.0e-10f, invlen;
	//_SSE_RSqrtInline(sqrlen, &invlen);
	vec.x *= invlen;
	vec.y *= invlen;
	vec.z *= invlen;
	return sqrlen * invlen;
}


FORCEINLINE float VectorNormalize(float* v)
{
	return VectorNormalize(*(reinterpret_cast< Vector * >(v)));
}

FORCEINLINE void VectorNormalizeFast(Vector& vec)
{
	VectorNormalize(vec);
}


inline vec_t Vector::NormalizeInPlace()
{
	return NormalizeVector(*this);
}

inline Vector Vector::Normalized() const
{
	Vector norm = *this;
	NormalizeVector(norm);
	return norm;
}

inline bool Vector::IsLengthGreaterThan(float val) const
{
	return LengthSqr() > val * val;
}

inline bool Vector::IsLengthLessThan(float val) const
{
	return LengthSqr() < val * val;
}