#ifndef GRAPHICENGINE_CLASS_H
#define GRAPHICENGINE_CLASS_H

#include <list>
#include "../GraphicEngine/GraphicObject.h"

class GraphicEngine
{
public:
	static GraphicEngine* _graphicengineptr;

	static GraphicEngine* GetInstance()
	{
		if (_graphicengineptr == nullptr)
		{
			_graphicengineptr = new GraphicEngine();
		}

		return _graphicengineptr;
	}

	void AddElementToDisplay(GraphicObject* object)
	{
		ElementToDisplay.push_back(object);
	}

private:

	std::list<GraphicObject*> ElementToDisplay;
};

#endif

