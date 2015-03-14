#ifndef CREATOR_HPP
#define CREATOR_HPP

#include "global.hpp"


class Anaglyph;
class Autostereogram;
class Flipbook;
class Photograph;

//! \class Creator
//! \brief Creator will be in charge of creating what the user asks
class Creator : public QObject{
	Q_OBJECT
public:

	//! \brief get instance of Creator
	static Creator* getCreator();

	//! \brief return the list of the name of anaglyph algorithm
	std::vector<QString> getListAnaglyph() const;

	//! \brief return the list of the name of autostereogram algorithm
	std::vector<QString> getListAutostereogram() const;

	//! \brief return the list of the name of flipbook algorithm
	std::vector<QString> getListFlipbook() const;

	//! \brief return the list of the name of photograph algorithm
	std::vector<QString> getListPhotograph() const;


public slots:

	//! \brief display a window where the user is able to configure and render
	//! \param The id of the algorithm that will be used.
	void launchAnaglyph(int fAlgoNumber = 0);

	//! \brief display a window where the user is able to configure and render
	//! \param The id of the algorithm that will be used.
	void launchAutostereogram(int fAlgoNumber = 0);

	//! \brief display a window where the user is able to configure and render
	//! \param The id of the algorithm that will be used.
	void launchFlipbook(int fAlgoNumber = 0);

	//! \brief display a window where the user is able to configure and render
	//! \param The id of the algorithm that will be used.
	void launchPhotograph(int fAlgoNumber = 0);


private:
	//! \brief Creator only has a default constructor
	Creator();

	template <class T>
	void launchAlgorithm(std::vector<T*>& fTable, int fAlgoNumber){
		for (auto _it : fTable){
			_it->hide();
		}

		if (fAlgoNumber < fTable.size()){
			fTable[fAlgoNumber]->launch();
			fTable[fAlgoNumber]->updatePreview();
		}
	}

	static Creator* mInstance;

	std::vector<Anaglyph*> mAnaglyphTable;
	std::vector<Autostereogram*> mAutostereogramTable;
	std::vector<Flipbook*> mFlipbookTable;
	std::vector<Photograph*> mPhotographTable;
};


#endif
