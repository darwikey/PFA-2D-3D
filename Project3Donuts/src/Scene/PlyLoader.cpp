#include "PlyLoader.hpp"
#include "Object.hpp"
#include "ObjLoader.hpp"



PlyLoader::PlyLoader(std::string fPath){
	std::cout << "Loading PLY file "<< fPath << std::endl;

	mFile.open(fPath);

}


PlyLoader::~PlyLoader(){

}


bool PlyLoader::load(Object* fObject) {
	if (!mFile)
		return false;
	
	parseHeader();

	std::cout << "parse vertices (" << mVerticesNumber << ")..." << std::endl;
	
	parseVertex(fObject);
	
	std::cout << "parse faces (" << mFacesNumber << ")..." << std::endl;
	parseFace(fObject);

	fObject->computeBoundingBox();

	return true;
}


void PlyLoader::parseHeader()
{
	bool _endProperty = false;
	std::vector<VerticesProperties> _verticesInfos;
    unsigned int _line_begining=0;
	
	// for each line
	std::string _line;
	while (std::getline(mFile, _line)){

        _line_begining = 0; 
		// We eat unwanted caracters. A header line begins with a word, so digit or spaces
        while(!((_line[_line_begining]>='A'&&_line[_line_begining]<='Z') || (_line[_line_begining]>='a'&&_line[_line_begining]<='z')) 
			&& _line_begining < _line.size()) {
            _line_begining++;
        }
        _line=_line.substr (_line_begining);

		std::istringstream _s (_line);

		std::string _word;
		std::getline(_s, _word, ' ');

		if (_word == "format"){
			std::getline(_s, _word, ' ');
			if (_word == "binary_little_endian"){
				mFormat = PlyFormat::BINARY_LITTLE_ENDIAN;
			}
			else if (_word == "binary_big_endian"){
				mFormat = PlyFormat::BINARY_BIG_ENDIAN;
			}
		}
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
	mVerticesFunction = [_verticesInfos, this](std::istream& fLine, Object* fObject)->void {

		QVector3D _position(0.f, 0.f, 0.f);
		QVector3D _normal(0.f, 0.f, 0.f);
		QVector3D _color(0.f, 0.f, 0.f);

		for (VerticesProperties i : _verticesInfos) {
			float _value = 0;
			if (this->mFormat == PlyFormat::ASCII){
				fLine >> _value;
			}
			else{
				if (i != VerticesProperties::RED && i != VerticesProperties::GREEN && i != VerticesProperties::BLUE){
					fLine.read(reinterpret_cast<char*>(&_value), sizeof(float));
				}
				else{
					uchar _smallValue = 0;
					fLine.read(reinterpret_cast<char*>(&_smallValue), sizeof(uchar));
					_value = (float)_smallValue;
				}
			}

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


void PlyLoader::parseVertex(Object* fObject)
{
	
	for (size_t i = 0; i < mVerticesNumber; i++) {
		if (mFormat == PlyFormat::ASCII){
			// get the line
			std::string _line;
			std::getline(mFile, _line);

			std::istringstream _s(_line);
		
			// extract the vertex property with the lambda expression
			mVerticesFunction(_s, fObject);
		}
		else{
			// extract the vertex property with the lambda expression
			mVerticesFunction(mFile, fObject);
		}
	}
}


void PlyLoader::parseFace(Object* fObject){
	if (mFormat == PlyFormat::ASCII){
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
				std::cerr << "parser don't support polygons which are not triangle or quad" << std::endl;
			}
		}
	}
	else{
		for (size_t i = 0; i < mFacesNumber; i++){
			uchar _verticesNumber;
			mFile.read(reinterpret_cast<char*>(&_verticesNumber), sizeof(uchar));

			// Triangle
			if (_verticesNumber == 3){
				for (size_t i = 0; i < _verticesNumber; i++) {
					uint _indice;
					mFile.read(reinterpret_cast<char*>(&_indice), sizeof(uint));
					fObject->pushIndice(_indice);
				}
			}
			// Quad
			else if (_verticesNumber == 4) {
				uint _indice[4];
				mFile.read(reinterpret_cast<char*>(&_indice), 4 * sizeof(uint));
				fObject->pushIndice(_indice[0]);
				fObject->pushIndice(_indice[1]);
				fObject->pushIndice(_indice[2]);
				fObject->pushIndice(_indice[0]);
				fObject->pushIndice(_indice[2]);
				fObject->pushIndice(_indice[3]);
			}
			else {
				std::cerr << "!!!" << _verticesNumber << " parser don't support polygons which are not triangle or quad" << std::endl;
			}
		}
	}
		
	
}
