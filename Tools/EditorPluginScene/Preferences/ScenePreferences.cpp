﻿#include <PCH.h>
#include <EditorPluginScene/Preferences/ScenePreferences.h>
#include <EditorEngineProcessFramework/EngineProcess/ViewRenderSettings.h>

EZ_BEGIN_STATIC_REFLECTED_TYPE(ezSceneViewPreferences, ezNoBase, 1, ezRTTIDefaultAllocator<ezSceneViewPreferences>)
{
  EZ_BEGIN_PROPERTIES
  {
    EZ_MEMBER_PROPERTY("CamPos", m_vCamPos),
    EZ_MEMBER_PROPERTY("CamDir", m_vCamDir),
    EZ_MEMBER_PROPERTY("CamUp", m_vCamUp),
    EZ_MEMBER_PROPERTY("Perspective", m_uiPerspectiveMode),
    EZ_MEMBER_PROPERTY("RenderMode", m_uiRenderMode),
    EZ_MEMBER_PROPERTY("FOV", m_fFov),
  }
  EZ_END_PROPERTIES
}
EZ_END_STATIC_REFLECTED_TYPE

EZ_BEGIN_DYNAMIC_REFLECTED_TYPE(ezScenePreferencesUser, 1, ezRTTIDefaultAllocator<ezScenePreferencesUser>)
{
  EZ_BEGIN_PROPERTIES
  {
    EZ_MEMBER_PROPERTY("ShowGrid", m_bShowGrid),
    EZ_MEMBER_PROPERTY("CameraSpeed", m_iCameraSpeed)->AddAttributes(new ezDefaultValueAttribute(15), new ezClampValueAttribute(1, 30)),
    EZ_MEMBER_PROPERTY("QuadView", m_bQuadView)->AddAttributes(new ezHiddenAttribute()),
    EZ_MEMBER_PROPERTY("ViewSingle", m_ViewSingle)->AddAttributes(new ezHiddenAttribute()),
    EZ_MEMBER_PROPERTY("ViewQuad0", m_ViewQuad0)->AddAttributes(new ezHiddenAttribute()),
    EZ_MEMBER_PROPERTY("ViewQuad1", m_ViewQuad1)->AddAttributes(new ezHiddenAttribute()),
    EZ_MEMBER_PROPERTY("ViewQuad2", m_ViewQuad2)->AddAttributes(new ezHiddenAttribute()),
    EZ_MEMBER_PROPERTY("ViewQuad3", m_ViewQuad3)->AddAttributes(new ezHiddenAttribute()),
  }
  EZ_END_PROPERTIES
}
EZ_END_DYNAMIC_REFLECTED_TYPE

ezScenePreferencesUser::ezScenePreferencesUser() : ezPreferences(Domain::Document, "Scene")
{
  m_bQuadView = false;
  m_iCameraSpeed = 9;

  m_ViewSingle.m_vCamPos.SetZero();
  m_ViewSingle.m_vCamDir.Set(1, 0, 0);
  m_ViewSingle.m_vCamUp.Set(0, 0, 1);
  m_ViewSingle.m_uiPerspectiveMode = ezSceneViewPerspective::Perspective;
  m_ViewSingle.m_uiRenderMode = ezViewRenderMode::Default;
  m_ViewSingle.m_fFov = 70.0f;

  // Top Left: Top Down
  m_ViewQuad0.m_vCamPos.SetZero();
  m_ViewQuad0.m_vCamDir.Set(0, 0, -1);
  m_ViewQuad0.m_vCamUp.Set(1, 0, 0);
  m_ViewQuad0.m_uiPerspectiveMode = ezSceneViewPerspective::Orthogonal_Top;
  m_ViewQuad0.m_uiRenderMode = ezViewRenderMode::WireframeMonochrome;
  m_ViewQuad0.m_fFov = 20.0f;

  // Top Right: Perspective
  m_ViewQuad1.m_vCamPos.SetZero();
  m_ViewQuad1.m_vCamDir.Set(1, 0, 0);
  m_ViewQuad1.m_vCamUp.Set(0, 0, 1);
  m_ViewQuad1.m_uiPerspectiveMode = ezSceneViewPerspective::Perspective;
  m_ViewQuad1.m_uiRenderMode = ezViewRenderMode::Default;
  m_ViewQuad1.m_fFov = 70.0f;

  // Bottom Left: Back to Front
  m_ViewQuad2.m_vCamPos.SetZero();
  m_ViewQuad2.m_vCamDir.Set(1, 0, 0);
  m_ViewQuad2.m_vCamUp.Set(0, 0, 1);
  m_ViewQuad2.m_uiPerspectiveMode = ezSceneViewPerspective::Orthogonal_Front;
  m_ViewQuad2.m_uiRenderMode = ezViewRenderMode::WireframeMonochrome;
  m_ViewQuad2.m_fFov = 20.0f;

  // Bottom Right: Right to Left
  m_ViewQuad3.m_vCamPos.SetZero();
  m_ViewQuad3.m_vCamDir.Set(0, -1, 0);
  m_ViewQuad3.m_vCamUp.Set(0, 0, 1);
  m_ViewQuad3.m_uiPerspectiveMode = ezSceneViewPerspective::Orthogonal_Right;
  m_ViewQuad3.m_uiRenderMode = ezViewRenderMode::WireframeMonochrome;
  m_ViewQuad3.m_fFov = 20.0f;
}

void ezScenePreferencesUser::SetCameraSpeed(ezInt32 value)
{
  m_iCameraSpeed = ezMath::Clamp(value, 0, 24);

  // Kiff, inform the men!
  TriggerPreferencesChangedEvent();
}

void ezScenePreferencesUser::SetShowGrid(bool show)
{
  m_bShowGrid = show;

  TriggerPreferencesChangedEvent();
}
