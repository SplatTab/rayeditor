#include "rayeditor.hpp"
#include "raystyles.hpp"
#include <math.h>
#include <raypatcher.h>
#include <rlImGui.h>

using namespace RayEditor;
using namespace RayEditor::Docks;

void SceneView::StartWindow()
{
    camera.zoom = 1;
    camera.target.x = 0;
    camera.target.y = 0;
    camera.rotation = 0;
    camera.offset.x = GetScreenWidth() / 2.0f;
    camera.offset.y = GetScreenHeight() / 2.0f;

    ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    UpdateSceneView();
}

void SceneView::DrawWindow(int dockID)
{
    if (!open)
    {
        DockManager::activeDocks.erase(DockManager::activeDocks.begin() + (dockID));
        return;
    }

    if (!Project::IsProjectLoaded) return;

    if (!dragging)
    {
        lastMousePos = GetMousePosition();
        lastCamTarget = camera.target;
    }
    else
    {
        Vector2 mousePos = GetMousePosition();
        Vector2 mouseDelta = Utility::RayVec2Subtract(lastMousePos, mousePos);;
        mouseDelta.x /= camera.zoom;
        mouseDelta.y /= camera.zoom;
        camera.target = Utility::RayVec2Add(lastCamTarget, mouseDelta);
        ReloadRenderTexture();
    }

    if (IsWindowResized() || Application::recompiling)
    {
        camera.offset.x = GetScreenWidth() / 2.0f;
        camera.offset.y = GetScreenHeight() / 2.0f;
        ReloadRenderTexture();
    }

    ImGui::SetNextWindowSizeConstraints(ImVec2{250, 500}, ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));

    if (ImGui::Begin(("Scene View##" + std::to_string(dockID)).c_str(), &open, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
    {
        size = ImGui::GetWindowSize();
        virtualRes = ImVec2(size.y * 2, size.y);
        ImGui::SetWindowSize(virtualRes);

        interactive = ImGui::IsWindowDocked() && ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows);

        if (IsMouseButtonDown(0) && interactive) dragging = true;
        else dragging = false;

        if (GetMouseWheelMove() > 0 && interactive)
        {
            dragging = false;
            camera.zoom += 0.05f;
            camera.target = Utility::RayVec2Add(camera.target, Utility::RayVec2Multiply(camera.target, Vector2{ 0.05f, 0.05f }));
            ReloadRenderTexture();
        }
        else if (GetMouseWheelMove() < 0 && camera.zoom > 0.09f && interactive)
        {
            dragging = false;
            camera.zoom -= 0.05f;
            camera.target = Utility::RayVec2Add(camera.target, Utility::RayVec2Multiply(camera.target, Vector2{ -0.05f, -0.05f }));
            ReloadRenderTexture();
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        viewRect.x = ViewTexture.texture.width / 2 - virtualRes.x / 2;
        viewRect.y = ViewTexture.texture.height / 2 - virtualRes.y / 2;
        viewRect.width = virtualRes.x;
        viewRect.height = -virtualRes.y;

        if (ImGui::BeginChild("Toolbar", ImVec2(size.x + 200, 25)))
        {
            ImGui::SetCursorPosX(2);
            ImGui::SetCursorPosY(3);
            ImGui::SameLine();
            ImGui::Text(("Camera-: X: " + std::to_string(camera.target.x) + " Y: " + std::to_string(camera.target.y) + " Zoom: " + std::to_string(camera.zoom)).c_str());

            ImGui::SameLine();
            ImGui::Dummy(ImVec2{10, 0});
            ImGui::SameLine();
            PushStyle::RayBlackInvertButtons();
            if (rlImGuiImageButton(&CachedIcons::cameracenter))
            {
                camera.zoom = 0.75f;
                camera.target = Vector2{ 960, 508 };
                ReloadRenderTexture();
            }
            PopStyle::RayBlackInvertButtons();
        }

        ImGui::EndChild();

        rlImGuiImageRect(&ViewTexture.texture, virtualRes.x, virtualRes.y, viewRect);
        ImGui::PopStyleVar(1);
    }

    ImGui::End();
}

void SceneView::ReloadRenderTexture()
{
    UnloadRenderTexture(ViewTexture);
    ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    UpdateSceneView();
}

void SceneView::UpdateSceneView()
{
    for (auto& object : RPatcher::m_rayBehaviours) object.RayObj->Close();
    for (auto& object : RPatcher::m_rayBehaviours) object.RayObj->Init();

    BeginTextureMode(ViewTexture);
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);

    for (auto& object : RPatcher::m_rayBehaviours) object.RayObj->Draw();

    EndMode2D();
    EndTextureMode();
}