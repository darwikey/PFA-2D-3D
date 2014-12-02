#include "PlyLoader.hpp"
#include "Model.hpp"



PlyLoader::PlyLoader(std::string fPath){
	std::cout << "Loading PLY file "<< fPath << std::endl;

	mFile.open(fPath);

	if (!mFile) {
		std::cerr << "Impossible to open the file ! Are you in the right path ?" << std::endl;
        exit(EXIT_FAILURE);
	}
}


PlyLoader::~PlyLoader(){

}


bool PlyLoader::load(Model* fModel) {
	parseHeader();

	std::cout << "parse vertices (" << mVerticesNumber << ")..." << endl;
	parseVertex(fModel);
	
	std::cout << "parse faces (" << mFacesNumber << ")..." << endl;
	parseFace(fModel);

	fModel->computeBoundingBox();

	return true;
}


void PlyLoader::parseHeader() {
	bool _endProperty = false;
	vector<VerticesProperties> _verticesInfos;
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
	mVerticesFunction = [_verticesInfos](std::istringstream& fLine, Model* fModel)->void {

		Vec3 _position(0.f, 0.f, 0.f);
		Vec3 _normal(0.f, 0.f, 0.f);
		Vec3 _color(0.f, 0.f, 0.f);

		for (VerticesProperties i : _verticesInfos) {

			switch (i) {
				case VerticesProperties::X:
				fLine >> _position.x;
				break;

				case VerticesProperties::Y:
				fLine >> _position.y;
				break;

				case VerticesProperties::Z:
				fLine >> _position.z;
				break;

				case VerticesProperties::NX:
				fLine >> _normal.x;
				break;

				case VerticesProperties::NY:
				fLine >> _normal.y;
				break;

				case VerticesProperties::NZ:
				fLine >> _normal.z;
				break;

				case VerticesProperties::RED:
				fLine >> _color.x;
				_color.x /= 255.f;
				break;

				case VerticesProperties::GREEN:
				fLine >> _color.y;
				_color.y /= 255.f;
				break;

				case VerticesProperties::BLUE:
				fLine >> _color.z;
				_color.z /= 255.f;
				break;
			}
		}

		// put the datas into the model
		fModel->vertices.push_back(_position);
		fModel->normals.push_back(_normal);
		fModel->color.push_back(_color);
	};
}


void PlyLoader::parseVertex(Model* fModel){
	
	for (size_t i = 0; i < mVerticesNumber; i++) {
		// get the line
		std::string _line;
		std::getline(mFile, _line);

		std::istringstream _s (_line);

		// extract the vertex property with the lambda expression
		mVerticesFunction(_s, fModel);
	}
}


void PlyLoader::parseFace(Model* fModel){
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
				fModel->indices.push_back(_indice);
			}
		}
		// Quad
		else if (_verticesNumber == 4) {
			uint _indice[4];
			_s >> _indice[0] >> _indice[1] >> _indice[2] >> _indice[3];
			fModel->indices.push_back(_indice[0]);
			fModel->indices.push_back(_indice[1]);
			fModel->indices.push_back(_indice[2]);
			fModel->indices.push_back(_indice[0]);
			fModel->indices.push_back(_indice[2]);
			fModel->indices.push_back(_indice[3]);
		}
		else {
			std::cerr << "parser don't support polygon which are not triangle or quad" << std::endl;
		}

		
	}
}
