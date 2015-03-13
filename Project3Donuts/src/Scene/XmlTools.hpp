#ifndef XML_TOOLS_HPP
#define XML_TOOLS_HPP

#include "global.hpp"
#include <QtXml/QDomDocument>
#include <QtXml/QDomNamedNodeMap>
#include <QtXml/QDomNodeList>
#include <QFile>

namespace XmlTools{

	void writeCoordinates(std::string &fStr, float fX, float fY, float fZ, int fTab) {
		int _i;
		for (_i = 0; _i<fTab; _i++) {
			fStr.append("\t");
		}
		fStr.append("<coordinates>\n");
		for (_i = 0; _i<fTab + 1; _i++) {
			fStr.append("\t");
		}
		fStr.append("<x>");
		fStr.append(std::to_string(fX));
		fStr.append("</x>\n");
		for (_i = 0; _i<fTab + 1; _i++) {
			fStr.append("\t");
		}
		fStr.append("<y>");
		fStr.append(std::to_string(fY));
		fStr.append("</y>\n");
		for (_i = 0; _i<fTab + 1; _i++) {
			fStr.append("\t");
		}
		fStr.append("<z>");
		fStr.append(std::to_string(fZ));
		fStr.append("</z>\n");
		for (_i = 0; _i<fTab; _i++) {
			fStr.append("\t");
		}
		fStr.append("</coordinates>\n");
	}

	void writeTranslation(std::string &fStr, float fX, float fY, float fZ, int fTab) {
		int _i;
		for (_i = 0; _i<fTab; _i++) {
			fStr.append("\t");
		}
		fStr.append("<translation>\n");
		writeCoordinates(fStr, fX, fY, fZ, fTab + 1);
		for (_i = 0; _i<fTab; _i++) {
			fStr.append("\t");
		}
		fStr.append("</translation>\n");
	}

	void writeRotation(std::string &fStr, float	fX, float fY, float fZ, int fTab) {
		int _i;
		for (_i = 0; _i<fTab; _i++) {
			fStr.append("\t");
		}
		fStr.append("<rotation>\n");
		writeCoordinates(fStr, fX, fY, fZ, fTab + 1);
		for (_i = 0; _i<fTab; _i++) {
			fStr.append("\t");
		}
		fStr.append("</rotation>\n");
	}

	void writeScale(std::string &fStr, float fX, float fY, float fZ, int fTab) {
		int _i;
		for (_i = 0; _i<fTab; _i++) {
			fStr.append("\t");
		}
		fStr.append("<scale>\n");
		writeCoordinates(fStr, fX, fY, fZ, fTab + 1);
		for (_i = 0; _i<fTab; _i++) {
			fStr.append("\t");
		}
		fStr.append("</scale>\n");
	}
};

#endif
