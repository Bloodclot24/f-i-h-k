#ifndef ABOUT_H_
#define ABOUT_H_

#include <gtkmm/aboutdialog.h>

#define ABOUT_NAME "Editor de diagramas"
#define ABOUT_VERSION "1.0"
#define ABOUT_COMMENTS "Permite diseñar, editar, imprimir y exportar diagramas."
#define ABOUT_LICENSE "GPL"
#define ABOUT_WEBSITE "http://code.assembla.com/taller/"
#define ABOUT_WEBSITE_LABEL "SVN"
#define ABOUT_AUTHOR_GRUPO "FireInTheHole"
#define ABOUT_AUTHOR_1 "Muñecas, Federico"
#define ABOUT_AUTHOR_2 "Mankowski, Daniel"
#define ABOUT_AUTHOR_3 "Rocha, Santiago"
#define ABOUT_AUTHOR_4 "Roberts, Karen"

class About : public Gtk::AboutDialog {
public:
	About() {
		set_program_name(ABOUT_NAME);
		set_version(ABOUT_VERSION);
		set_comments(ABOUT_COMMENTS);
		set_license(ABOUT_LICENSE);
		set_website(ABOUT_WEBSITE);
		set_website_label(ABOUT_WEBSITE_LABEL);
		std::vector<std::string> authors;
		authors.push_back(ABOUT_AUTHOR_GRUPO);
		authors.push_back(ABOUT_AUTHOR_1);
		authors.push_back(ABOUT_AUTHOR_2);
		authors.push_back(ABOUT_AUTHOR_3);
		authors.push_back(ABOUT_AUTHOR_4);
		set_authors(authors);
	}
	virtual ~About() { }
};

#endif /* ABOUT_H_ */
