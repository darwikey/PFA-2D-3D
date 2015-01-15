#include "ObjLoader.hpp"
#include "Object.hpp"


using namespace std;

ObjLoader::ObjLoader(std::string fPath){
	std::cout << "Loading Obj file " << fPath << std::endl;

	mFile.open(fPath);

}


ObjLoader::~ObjLoader(){
}


bool ObjLoader::load(Object* fObject){
    if (!mFile)
        return false;
	string _line;
	size_t hashIndex = 0;

	// Visit each line of the obj file
	while (getline(mFile, _line))
	{
		if (_line.size() < 3)
			continue;

		// Extract vertex
		// Line starts with v[space]...
		if (_line[0] == 'v' && _line[1] == ' ')
		{
			string _lineVals = _line.substr(2);
			QVector3D _val;

			string val0 = _lineVals.substr(0, _lineVals.find(' '));
			_val.setX((float) atof(val0.c_str()));
		
			string val1 = _lineVals.substr(val0.length() + 1,
										  _lineVals.find(' '));
			_val.setY((float) atof(val1.c_str()));
			
			string val2 = _lineVals.substr(_lineVals.find_last_of(' ') + 1);
			_val.setZ((float) atof(val2.c_str()));

			fObject->pushVertice(_val);
		}


		// Extract textures
		// line starts with vt[space]...
		else if (_line[0] == 'v' && _line[1] == 't' && _line[2] == ' ')
		{
			string _lineVals = _line.substr(3);
			QVector2D _val;

			string val0 = _lineVals.substr(0, _lineVals.find(' '));
			_val.setX((float) atof(val0.c_str()));
			
			string val1 = _lineVals.substr(val0.length() + 1, _lineVals.find(' '));
			_val.setY((float) atof(val1.c_str()));
			
			fObject->pushTextureCoordinate(_val);
		}


		// Extract normals
		// Line starts with vn[space]...
		else if (_line[0] == 'v' && _line[1] == 'n' && _line[2] == ' ')
		{
			string _lineVals = _line.substr(3);
			QVector3D _val;

			string val0 = _lineVals.substr(0, _lineVals.find(' '));
			_val.setX((float) atof(val0.c_str()));

			string val1 = _lineVals.substr(val0.length() + 1,
										  _lineVals.find(' '));
			_val.setY((float) atof(val1.c_str()));

			string val2 = _lineVals.substr(_lineVals.find_last_of(' ') + 1);
			_val.setZ((float) atof(val2.c_str()));
			
			fObject->pushNormal(_val);
		}


		//
		// 2. Hash faces
		//
		// Extract faces
		// Line starts with f[space]...
		else if (_line[0] == 'f' && _line[1] == ' ') 
		{
			istringstream _lineVals (_line.substr(2));
			string _group;

			while (std::getline(_lineVals, _group, ' ')) {

				istringstream _sgroup(_group);
				string _s;
				size_t _i = 0;

				while (std::getline(_sgroup, _s, '/')) {
					if (!_s.empty()) {
						uint _value = atoi(_s.c_str()) - 1;

						switch(_i) {
						case 0:
							fObject->pushIndice(_value);
							break;
						case 1:
							//TODO fObject->uvsIndice.push_back(_value);
							break;

						case 2:
							//TODO fObject->normalIndices.push_back(_value);
							break;
						}
					}

					_i++;
				}

			}
		}
	}


	std::cout << "Finished extracting values from file" << endl;
	/*	<< "Quick count check:" << endl
		<< "\tVerts = " << fObject->vertices.size() << endl
		<< "\tNorms = " << fObject->normals.size() << endl
		<< "\tTexts = " << fObject->uvs.size() << endl
		<< "\tFaces = " << fObject->indices.size() / 3 << endl;*/


	fObject->computeBoundingBox();

	return true;
}

