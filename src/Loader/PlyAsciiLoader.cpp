#include "PlyAsciiLoader.hpp"
#include "Object.hpp"



PlyAsciiLoader::PlyAsciiLoader(std::string fPath){
	std::cout << "Loading PLY file "<< fPath << std::endl;

	mFile.open(fPath);

	if (!mFile) {
		std::cerr << "Impossible to open the file ! Are you in the right path ?" << std::endl;
        exit(EXIT_FAILURE);
	}
}


PlyAsciiLoader::~PlyAsciiLoader(){

}


bool PlyAsciiLoader::load(Object* fObject) {
	parseHeader();

	std::cout << "parse vertices (" << mVerticesNumber << ")..." << endl;
	parseVertex(fObject);
	
	std::cout << "parse faces (" << mFacesNumber << ")..." << endl;
	parseFace(fObject);

	fObject->computeBoundingBox();

	return true;
}


void PlyAsciiLoader::parseHeader() {
	bool _endProperty = false;
	std::vector<VerticesProperties> _verticesInfos;
    unsigned int _line_begining=0;
	// for each line
	std::string _line;

	while (std::getline(mFile, _line)){

        _line_begining=0; //we eat unwanted caracters. A header line begins with a word, so digit or spaces
        while(!((_line[_line_begining]>='A'&&_line[_line_begining]<='Z')||(_line[_line_begining]>='a'&&_line[_line_begining]<='z'))&&_line_begining<_line.size()){
            _line_begining++;
        }
        _line=_line.substr (_line_begining);

		std::istringstream _s (_line);

		std::string _word;
		std::getline(_s, _word, ' ');

		if (_word == "element") {
			std::getline(_s, _word, ' ');

			if (_word == "vertex") {
				_s >> mVerticesNumber;
			}
			else if (_word == "face") {
				_s >> mFacesNumber;
				_endProperty = true;
			}
		}

		if (!_endProperty && _word == "property") {
			std::getline(_s, _word, ' ');
			std::getline(_s, _word, ' ');

			if (_word == "x") {
				_verticesInfos.push_back(VerticesProperties::X);	
			}
			else if (_word == "y") {
				_verticesInfos.push_back(VerticesProperties::Y);	
			}
			else if (_word == "z") {
				_verticesInfos.push_back(VerticesProperties::Z);	
			}
			else if (_word == "nx") {
				_verticesInfos.push_back(VerticesProperties::NX);	
			}
			else if (_word == "ny") {
				_verticesInfos.push_back(VerticesProperties::NY);	
			}
			else if (_word == "nz") {
				_verticesInfos.push_back(VerticesProperties::NZ);	
			}
			else if (_word == "red") {
				_verticesInfos.push_back(VerticesProperties::RED);	
			}
			else if (_word == "green") {
				_verticesInfos.push_back(VerticesProperties::GREEN);	
			}
			else if (_word == "blue") {
				_verticesInfos.push_back(VerticesProperties::BLUE);	
			}
			else {
				std::cerr << "unknown vertex property : " << _word << endl;
			}
		}

		if (_word == "end_header") {
			break;
		}
	}

	// Lambda expression create in order to parse vertex datas later
	mVerticesFunction = [_verticesInfos](std::istringstream& fLine, Object* fObject)->void {

		QVector3D _position(0.f, 0.f, 0.f);
		QVector3D _normal(0.f, 0.f, 0.f);
		QVector3D _color(0.f, 0.f, 0.f);

		for (VerticesProperties i : _verticesInfos) {
			float _value = 0;
			fLine >> _value;

			switch (i) {
				case VerticesProperties::X:
				_position.setX(_value);
				break;

				case VerticesProperties::Y:
				_position.setY(_value);
				break;

				case VerticesProperties::Z:
				_position.setZ(_value);
				break;

				case VerticesProperties::NX:
				_normal.setX(_value);
				break;

				case VerticesProperties::NY:
				_normal.setY(_value);
				break;

				case VerticesProperties::NZ:
				_normal.setZ(_value);
				break;

				case VerticesProperties::RED:
				_color.setX(_value / 255);
				break;

				case VerticesProperties::GREEN:
				_color.setY(_value / 255);
				break;

				case VerticesProperties::BLUE:
				_color.setZ(_value / 255);
				break;
			}
		}

		// put the datas into the Object
		fObject->pushVertice(_position);
		fObject->pushNormal(_normal);
		fObject->pushColor(_color);
	};
}


void PlyAsciiLoader::parseVertex(Object* fObject){
	
	for (size_t i = 0; i < mVerticesNumber; i++) {
		// get the line
		std::string _line;
		std::getline(mFile, _line);

		std::istringstream _s (_line);

		// extract the vertex property with the lambda expression
		mVerticesFunction(_s, fObject);
	}
}


void PlyAsciiLoader::parseFace(Object* fObject){
	// for each line
	std::string _line;
	while (std::getline(mFile, _line)){
		std::istringstream _s (_line);

		size_t _verticesNumber;
		_s >> _verticesNumber;

		// Triangle
		if (_verticesNumber == 3){
			for (size_t i = 0; i < _verticesNumber; i++) {
				uint _indice;
				_s >> _indice;
				fObject->pushIndice(_indice);
			}
		}
		// Quad
		else if (_verticesNumber == 4) {
			uint _indice[4];
			_s >> _indice[0] >> _indice[1] >> _indice[2] >> _indice[3];
			fObject->pushIndice(_indice[0]);
			fObject->pushIndice(_indice[1]);
			fObject->pushIndice(_indice[2]);
			fObject->pushIndice(_indice[0]);
			fObject->pushIndice(_indice[2]);
			fObject->pushIndice(_indice[3]);
		}
		else {
			std::cerr << "parser don't support polygon which are not triangle or quad" << std::endl;
		}

		
	}
}
