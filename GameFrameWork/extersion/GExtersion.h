#ifndef __GEXTERSION__
#define __GEXTERSION__

//tinyxml解析库
#include "tinyxml/tinyxml.h"
//regex正则表达式库(pcre2实现)
#include "regex/GRegex.h"

//数据类型
#include "DataStruct/GQuadTree.h"
#include "DataStruct/GString.h"
#include "DataStruct/ObjectPool.hpp"
#include "DataStruct/GValue.h"

//2d数学模型
#include "Math/Point.h"
#include "Math/Rect2D.h"
#include "Math/Rect3D.h"
#include "Math/Size.h"

//容器类型
#include "Container/Map.hpp"
#include "Container/Set.h"
#include "Container/Vector.hpp"

//调试工具
#include "DebugUtils/DebugUtils.h"
//IO工具
#include "DataIOUtils/DataIOUtils.h"

//单例
#include "SingleInstance.h"

//不可拷贝基类
#include "nocopy/nocopy.h"

#endif