#include "rayeditor.hpp"
#include <rlImGui.h>

using namespace RayEditor::Docks;

Camera2D camera;

void SceneView::StartWindow() {
    camera.zoom = 1;
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

    if (IsWindowResized()) {
        UnloadRenderTexture(ViewTexture);
        ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
        camera.offset.x = GetScreenWidth() / 2.0f;
        camera.offset.y = GetScreenHeight() / 2.0f;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::SetNextWindowSizeConstraints(ImVec2(400, 400), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));
    ImVec2 size = ImGui::GetContentRegionAvail();

    ImGui::Begin(("Scene View##" + std::to_string(dockID)).c_str(), &open, ImGuiWindowFlags_NoScrollbar);

    // center the scratch pad in the view
    Rectangle viewRect = { 0 };
    viewRect.x = ViewTexture.texture.width / 2 - size.x / 2;
    viewRect.y = ViewTexture.texture.height / 2 - size.y / 2;
    viewRect.width = size.x;
    viewRect.height = -size.y;

    if (ImGui::BeginChild("Toolbar", ImVec2(ImGui::GetContentRegionAvail().x, 25)))
    {
        ImGui::SetCursorPosX(2);
        ImGui::SetCursorPosY(3);
        ImGui::SameLine();
        ImGui::TextUnformatted(TextFormat("camera target X%f Y%f", camera.target.x, camera.target.y));
        ImGui::EndChild();
    }

    rlImGuiImageRect(&ViewTexture.texture, (int)size.x, (int)size.y, viewRect);

    ImGui::PopStyleVar(1);
    ImGui::End();
}

void SceneView::UpdateSceneView() {
    BeginTextureMode(ViewTexture);
    ClearBackground(BLUE);
    BeginMode2D(camera);
    DrawTexture(CachedIcons::defaultFile, CachedIcons::defaultFile.width / -2, CachedIcons::defaultFile.height / -2, WHITE);
    EndMode2D();
    EndTextureMode();
}