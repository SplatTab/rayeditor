#include "rayeditor.hpp"
#include <raypatcher.h>
#include <rlImGui.h>

using namespace RayEditor;
using namespace RayEditor::Docks;

Camera2D camera;
bool dragging;
Vector2 lastMousePos;
Vector2 lastCamTarget;

void SceneView::StartWindow() {
    camera.zoom = 0.15f;
    camera.target.x = 0;
    camera.target.y = 0;
    camera.rotation = 0;
    camera.offset.x = GetScreenWidth() / 2.0f;
    camera.offset.y = GetScreenHeight() / 2.0f;

    ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    UpdateSceneView();
}

void SceneView::DrawWindow(int dockID) {
    if (!open) {
        DockManager::activeDocks.erase(DockManager::activeDocks.begin() + (dockID));
        return;
    }

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
        UnloadRenderTexture(ViewTexture);
        ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
        UpdateSceneView();
    }

    if (IsWindowResized() || Application::recompiling) {
        UnloadRenderTexture(ViewTexture);
        ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
        camera.offset.x = GetScreenWidth() / 2.0f;
        camera.offset.y = GetScreenHeight() / 2.0f;
        UpdateSceneView();
    }

    ImVec2 size = ImGui::GetContentRegionAvail();
    ImGui::SetNextWindowSizeConstraints(size, ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));

    if (ImGui::Begin(("Scene View##" + std::to_string(dockID)).c_str(), &open, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
    {
        Vector2 cameraPos = camera.target;
        if (GetMouseWheelMove() > 0 && camera.zoom > 0.1f)
        {
            camera.zoom -= 0.1f;
            camera.target = Vector2{cameraPos.x / camera.zoom, cameraPos.y / camera.zoom};
            UnloadRenderTexture(ViewTexture);
            ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
            UpdateSceneView();
        }
        else if (GetMouseWheelMove() < 0 && camera.zoom < 2)
        {
            camera.zoom += 0.1f / camera.zoom;
            camera.target = Utility::RayVec2Subtract(cameraPos, Vector2 { cameraPos.x / 2, cameraPos.y / 2});
            UnloadRenderTexture(ViewTexture);
            ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
            UpdateSceneView();
        }

        if (IsMouseButtonDown(0) && ImGui::IsWindowDocked() && ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows)) dragging = true;
        else dragging = false;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        Rectangle viewRect = { 0 };
        viewRect.x = ViewTexture.texture.width / 2 - size.x / 2;
        viewRect.y = ViewTexture.texture.height / 2 - size.y / 2;
        viewRect.width = size.x;
        viewRect.height = -size.y;

        if (ImGui::BeginChild("Toolbar", ImVec2(size.x, 25)))
        {
            ImGui::SetCursorPosX(2);
            ImGui::SetCursorPosY(3);
            ImGui::SameLine();
            ImGui::TextUnformatted(TextFormat("Camera Position X%f Y%f", camera.target.x, camera.target.y));
        }

        ImGui::EndChild();

        float aspect = ImGui::GetWindowSize().x;
        rlImGuiImageRect(&ViewTexture.texture, aspect, aspect, viewRect);
        ImGui::PopStyleVar(1);
    }

    ImGui::End();
}

void SceneView::UpdateSceneView() {
    for (auto& object : RPatcher::m_rayBehaviours) object.RayObj->Close();
    for (auto& object : RPatcher::m_rayBehaviours) object.RayObj->Init();

    BeginTextureMode(ViewTexture);
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);

    for (auto& object : RPatcher::m_rayBehaviours) object.RayObj->Draw();

    EndMode2D();
    EndTextureMode();
}