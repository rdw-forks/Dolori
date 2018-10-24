#include "SceneGraphNode.h"

CSceneGraphNode::CSceneGraphNode()
    : m_parent(),
      m_child(),
      m_center(),
      m_halfSize(),
      m_needUpdate(),
      m_ground(),
      m_attr() {}

CSceneGraphNode::~CSceneGraphNode() {}
