/*
* Draw.cpp : Contains the implementation for the wrapped ImGui Drawing functions 
*/

/* Includes for this file */
#include "Draw.hpp"
#include "../../Vendors/ImGui/imgui_internal.h"

/* Implementation for drawing text */
void Draw::Text(ImVec2 pos, ImColor col, std::string str, DrawFlags flags)
{
	/* Check that text is within the bounds of the screen */
	if ((pos.x <= 0.0 || pos.y <= 0.0) || (pos.x >= GetSystemMetrics(SM_CXSCREEN) || pos.y >= GetSystemMetrics(SM_CYSCREEN)))
	{
		if (flags & BOUNDS) return;
	}

	/* Get the ImGui window class */
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	/* Check if the centered text flag was applied */
	if (flags & CENTERED)
	{
		/* Update the text position to the center */
		pos.x -= (ImGui::CalcTextSize(str.c_str()).x) / 2.0f;
	}

	/* Check if the outline text flag was applied */
	if (flags & OUTLINE)
	{
		window->DrawList->AddText(pos, ImColor(0.0f, 0.0f, 0.0f, 1.0f), str.c_str());
	}

	/* Add text to draw list */
	window->DrawList->AddText(pos, col, str.c_str());

}

/* Implementation for drawing a line */
void Draw::Line(ImVec2 pt, ImVec2 pb, ImColor col, int thickness, DrawFlags flags)
{
	/* Check if the rect is within bounds of the render frame */
	if ((pt.x <= 0.0 || pt.y <= 0.0) || (pt.x >= GetSystemMetrics(SM_CXSCREEN) || pt.y >= GetSystemMetrics(SM_CYSCREEN))
		|| (pb.x <= 0.0 || pb.y <= 0.0) || (pb.x >= GetSystemMetrics(SM_CXSCREEN) || pb.y >= GetSystemMetrics(SM_CYSCREEN)))
	{
		if (flags & BOUNDS) return;
	}

	/* Get the ImGui window class */
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	/* Distinguish whether flag specified wanted an outline */
	if (flags & OUTLINE)
	{
		/* Draw the outline of the line */
		window->DrawList->AddLine(pt, pb, ImColor(0.0f, 0.0f, 0.0f, 1.0f), thickness + 3);
	}

	/* Draw the outline of the line */
	window->DrawList->AddLine(pt, pb, col, thickness);
}

/* Implementation for drawing a circle */
void Draw::Circle(ImVec2 pos, ImColor col, int radius, int thickness, int segments, DrawFlags flags)
{
	/* Check that text is within the bounds of the screen */
	if ((pos.x <= 0.0 || pos.y <= 0.0) || (pos.x >= GetSystemMetrics(SM_CXSCREEN) || pos.y >= GetSystemMetrics(SM_CYSCREEN)))
	{
		if (flags & BOUNDS) return;
	}

	/* Get the ImGui window class */
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	/* Distinguish whether flag specified wanted an outline */
	if (flags & OUTLINE)
	{
		/* Draw the outline of the circle */
		window->DrawList->AddCircle(pos, radius, ImColor(0.0f, 0.0f, 0.0f, 1.0f), segments, thickness + 3);
	}

	/* Distinguish whether the flag specified wanted a solid object */
	if (flags & SOLID)
	{
		/* Draw a solid circle */
		window->DrawList->AddCircleFilled(pos, radius, col, segments);
	}
	else
	{
		/* Draw a Cricle if solid wasnt specified */
		window->DrawList->AddCircle(pos, radius, col, segments, thickness);
	}
}

/* Implementation for drawing a rectangle */
void Draw::Rectangle(ImVec2 pt, ImVec2 pb, ImColor col, int thickness, float rounding, ImDrawCornerFlags corner_flags, DrawFlags flags)
{
	/* Check if the rect is within bounds of the render frame */
	if ((pt.x <= 0.0 || pt.y <= 0.0) || (pt.x >= GetSystemMetrics(SM_CXSCREEN) || pt.y >= GetSystemMetrics(SM_CYSCREEN))
		|| (pb.x <= 0.0 || pb.y <= 0.0) || (pb.x >= GetSystemMetrics(SM_CXSCREEN) || pb.y >= GetSystemMetrics(SM_CYSCREEN)))
	{
		if (flags & BOUNDS) return;
	}

	/* Get the ImGui window class */
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	/* Distinguish whether flag specified wanted an outline */
	if (flags & OUTLINE)
	{
		/* Draw the outline of the rectangle */
		window->DrawList->AddRect(pt, pb, ImColor(0.0f, 0.0f, 0.0f, 1.0f), rounding, corner_flags, thickness + 3);
	}

	/* Distinguish whether the flag specified wanted a solid object */
	if (flags & SOLID)
	{
		/* Draw the solid rectangle */
		window->DrawList->AddRectFilled(pt, pb, col, rounding, corner_flags);
	}
	else
	{
		/* Draw a rectangle if solid wasnt specified */
		window->DrawList->AddRect(pt, pb, col, rounding, corner_flags, thickness);
	}
}

/* Implementation for the X cross hair */
void Draw::XCrossHair(ImColor col)
{
	/* Create a pos vector (( Center of the screen )) */
	ImVec2 center = ImVec2(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);

	/* Draw crosshair outline -- yes, drawrect would save 4 lines here, idc nigger */
	ImColor outlinecol = ImColor(0.0f, 0.0f, 0.0f);
	/* HORIZONTAL */
	this->Line(ImVec2(center.x - 6, center.y - 1), ImVec2(center.x + 5, center.y - 1), outlinecol, 1, NONE);
	this->Line(ImVec2(center.x - 6, center.y), ImVec2(center.x + 5, center.y), outlinecol, 1, NONE);
	this->Line(ImVec2(center.x - 6, center.y + 1), ImVec2(center.x + 5, center.y + 1), outlinecol, 1, NONE);
	/* VERTICAL */
	this->Line(ImVec2(center.x - 2, center.y - 5), ImVec2(center.x - 2, center.y + 6), outlinecol, 1, NONE);
	this->Line(ImVec2(center.x - 1, center.y - 5), ImVec2(center.x - 1, center.y + 6), outlinecol, 1, NONE);
	this->Line(ImVec2(center.x, center.y - 5), ImVec2(center.x , center.y + 6), outlinecol, 1, NONE);

	/* Draw crosshair */
	this->Line(ImVec2(center.x - 5, center.y), ImVec2(center.x + 4, center.y), col, 1, NONE); // horizontal
	this->Line(ImVec2(center.x - 1, center.y - 4), ImVec2(center.x - 1, center.y + 5), col, 1, NONE); // vertical
}

Draw* draw = new Draw;