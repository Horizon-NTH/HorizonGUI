#pragma once

#include "Include.h"

class PyWidget : public hgui::kernel::Widget
{
public:
	using Widget::Widget;

	void set_size(const hgui::size& newSize) override;
	void set_position(const hgui::point& newPosition) override;
	void draw() const override;
	bool is_inside(const hgui::point& point) const override;
};

class PySprite : public hgui::kernel::Sprite
{
public:
	using Sprite::Sprite;
	void set_position(const hgui::point& newPosition) override;
	void set_size(const hgui::size& newSize) override;
	void draw() const override;
	bool is_inside(const hgui::point& point) const override;
};
