

#ifdef __PC_SIMULATOR__
#define cpfsqrt sqrtf
#define cpfsin sinf
#define cpfcos cosf
#define cpfacos acosf
#define cpfatan2 atan2f
#define cpfmod fmodf
#define cpfexp expf
#define cpfpow powf
#define cpffloor floorf
#define cpfceil ceilf
#else
#define cpfsqrt sqrt
#define cpfsin sin
#define cpfcos cos
#define cpfacos acos
#define cpfatan2 atan2
#define cpfmod fmod
#define cpfexp exp
#define cpfpow pow
#define cpffloor floor
#define cpfceil ceil
#endif

#ifndef M_PI
#define M_PI 3.141592653589f
#endif

#ifndef M_E
#define M_E  2.718281828459f
#endif

typedef float cpFloat;
typedef struct cpVect{cpFloat x,y;} cpVect;



#ifndef INFINITY
	//TODO use C++ infinity

		union MSVC_EVIL_FLOAT_HACK
		{
			unsigned char Bytes[4];
			float Value;
		};
		static union MSVC_EVIL_FLOAT_HACK INFINITY_HACK = {{0x00, 0x00, 0x80, 0x7F}};
	#define INFINITY (INFINITY_HACK.Value)
#endif



/// Return the max of two cpFloats.
static __inline cpFloat cpfmax(cpFloat a, cpFloat b)
{
	return (a > b) ? a : b;
}

/// Return the min of two cpFloats.
static __inline cpFloat cpfmin(cpFloat a, cpFloat b)
{
	return (a < b) ? a : b;
}

/// Return the absolute value of a cpFloat.
static __inline cpFloat cpfabs(cpFloat f)
{
	return (f < 0) ? -f : f;
}

/// Clamp @c f to be between @c min and @c max.
static __inline cpFloat cpfclamp(cpFloat f, cpFloat min, cpFloat max)
{
	return cpfmin(cpfmax(f, min), max);
}

/// Linearly interpolate (or extrapolate) between @c f1 and @c f2 by @c t percent.
static __inline cpFloat cpflerp(cpFloat f1, cpFloat f2, cpFloat t)
{
	return f1*(1.0f - t) + f2*t;
}

/// Linearly interpolate from @c f1 to @c f2 by no more than @c d.
static __inline cpFloat cpflerpconst(cpFloat f1, cpFloat f2, cpFloat d)
{
	return f1 + cpfclamp(f2 - f1, -d, d);
}

/// Hash value type.
typedef unsigned int cpHashValue;

/// Chipmunk's boolean type.
/// Oh C, how we love to define our own boolean types to get compiler compatibility
#ifdef CP_BOOL_TYPE
	typedef CP_BOOL_TYPE cpBool;
#else
	typedef int cpBool;
#endif

#ifndef cpTrue
/// true value.
	#define cpTrue 1
#endif

#ifndef cpFalse
/// false value.
	#define cpFalse 0
#endif

#ifdef CP_DATA_POINTER_TYPE
	typedef CP_DATA_POINTER_TYPE cpDataPointer;
#else
/// Type used for user data pointers.
	typedef void * cpDataPointer;
#endif

#ifdef CP_COLLISION_TYPE_TYPE
	typedef CP_COLLISION_TYPE_TYPE cpCollisionType;
#else
/// Type used for cpSpace.collision_type.
	typedef unsigned int cpCollisionType;
#endif

#ifdef CP_GROUP_TYPE
	typedef CP_GROUP_TYPE cpGroup;
#else
/// Type used for cpShape.group.
	typedef unsigned int cpGroup;
#endif

#ifdef CP_LAYERS_TYPE
	typedef CP_GROUP_TYPE cpLayers;
#else
/// Type used for cpShape.layers.
	typedef unsigned int cpLayers;
#endif

#ifdef CP_TIMESTAMP_TYPE
	typedef CP_TIMESTAMP_TYPE cpTimestamp;
#else
/// Type used for various timestamps in Chipmunk.
	typedef unsigned int cpTimestamp;
#endif

#ifndef CP_NO_GROUP
/// Value for cpShape.group signifying that a shape is in no group.
	#define CP_NO_GROUP ((cpGroup)0)
#endif

#ifndef CP_ALL_LAYERS
/// Value for cpShape.layers signifying that a shape is in every layer.
	#define CP_ALL_LAYERS (~(cpLayers)0)
#endif
/// @}


