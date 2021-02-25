#ifndef CUBE_FORMULADETAILSWIDGET_H
#define CUBE_FORMULADETAILSWIDGET_H
#include "BaseWidget.h"
#include "../plasma/Node.h"
#include "Item.h"
#include "../common/Vector3.h"
namespace cube {
class Game;
class FormulaDetailsWidget : public cube::BaseWidget {
    public:
		FloatVector3 result_item_rotation;
		int field_1F4;
		cube::Item result_item;
		int workstation_required;
		int field_29C;
		__int64 field_2A0;
		__int64 field_2A8;
		__int64 field_2B0;
		__int64 field_2B8;
		cube::Game* game;
		plasma::Node* itemshadow;
		plasma::Node* craftbutton;
		plasma::Node* craftbar;
		plasma::Node* craftbar_bar;
		int field_2E8;
		cube::Item unk_item;
		char field_38C;
		char field_38D;
		char field_38E;
		char field_38F;
    };
}

static_assert(sizeof(cube::FormulaDetailsWidget) == 0x390, "cube::FormulaDetailsWidget is not the correct size.");

#endif // CUBE_FORMULADETAILSWIDGET_H
