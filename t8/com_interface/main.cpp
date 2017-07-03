#include <string>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <FL/fl_ask.H>
#include <vector>
#include <iostream>
#include "window.h"
#include <FL/Fl_File_Chooser.H>

#include <thread>
#include <fstream>
#include <sstream>
#include <mutex>          // std::mutex

void delSpaces(std::string &str)
{
   str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

class CSV {

private:

//    | Comando | Tipo | Label | Nome |

    std::string Command;
    std::string Type;
    std::string Label;
    std::string Name;

public:

    CSV(std::string Command, std::string Type, std::string Label, std::string Name){

        this->Command = Command;
        this->Type = Type;
        this->Label = Label;
        this->Name = Name;
    }

    std::string getCommand(){
        return Command;
    }

    std::string getType(){
        return Type;
    }

    std::string getLabel(){
        return Label;
    }

    std::string getName(){
        return Name;
    }


};


// todo -->> metodo para liberar memoria
class CSV_Editor {

private:

    std::vector<CSV*> CSVvector;
    std::ofstream CSV_file;
    int Total_lines = 0;

public:


    void free( void ){


    }


     void insert_line(std::string Command, std::string Type, std::string Label, std::string Name){
        CSV *csvType = new CSV(Command, Type, Label, Name);
        CSVvector.push_back(csvType);
        Total_lines++;

    }

    void list_commands( void ){
        int count = 1;
        for (auto i = CSVvector.begin(); i != CSVvector.end(); i++){
            //CSV *teste = i;
            std::cout<< "+  " << count << ". {" << (*i)->getCommand() << ", " << (*i)->getType()<< ", " << (*i)->getLabel()<< ", " << (*i)->getName() << '}' << std::endl;
            count++;
        }
    }

    void delete_line(int line_number){

        if(line_isValid(line_number) == false)
            return;

        delete CSVvector[line_number-1];
        CSVvector.erase(CSVvector.begin()+(line_number-1));


    }

    void edit_entire_line(int line_number, std::string Command, std::string Type, std::string Label, std::string Name){

        if(line_isValid(line_number) == false)
            return;
        CSV *csvType = new CSV(Command, Type, Label, Name);
        delete_line(line_number);
        CSVvector.insert(CSVvector.begin() + (line_number-1), csvType);


    }

    void edit_line_element(int line_number, int element, std::string new_element){

        if(line_isValid(line_number) == false)
            return;

        switch(element){

            case 1: edit_entire_line(line_number, new_element, CSVvector.at(line_number-1)->getType(), CSVvector.at(line_number-1)->getLabel(), CSVvector.at(line_number-1)->getName()); break;
            case 2: edit_entire_line(line_number,CSVvector.at(line_number-1)->getCommand(), new_element, CSVvector.at(line_number-1)->getLabel(), CSVvector.at(line_number-1)->getName()); break;
            case 3: edit_entire_line(line_number,CSVvector.at(line_number-1)->getCommand(), CSVvector.at(line_number-1)->getType(), new_element, CSVvector.at(line_number-1)->getName()); break;
            case 4: edit_entire_line(line_number,CSVvector.at(line_number-1)->getCommand(), CSVvector.at(line_number-1)->getType(), CSVvector.at(line_number-1)->getLabel(), new_element); break;
            default: std::cout << "ERROR: Invalid element number. Operation could not be done."  << std::endl;

        }
    }

    std::string get_PageTitle( void ){

    	return CSVvector.at(2)->getName();

    }

    std::string get_WebPage_name( void ){

      	return CSVvector.at(1)->getName();

     }

    bool line_isValid(int line_number){

        if((line_number-1) < 0 || (line_number-1) > CSVvector.size()){
            std::cout << "ERROR: Invalid line number. Operation in [line " << line_number << "] could not be done."  << std::endl;
            return false;
        } else return true;

    }

    bool save_project(std::string file_name){

    	CSV_file.open(file_name.data());
    	if(!CSV_file.is_open()){
    		return false;
    	}

    	for (auto i = CSVvector.begin(); i != CSVvector.end(); i++){
    		//CSV *teste = i;
    		CSV_file << (*i)->getCommand() << "," << (*i)->getType()<< "," << (*i)->getLabel()<< "," << (*i)->getName() << std::endl;

    	}

    	CSV_file.close();
    	return true;
    }

    bool load_project(std::string file_name){

    	//todo verificar se arquivo está correto.
    	//todo salvar nome do projeto e nome do arquivo

    	std::ifstream data(file_name.data());

    	std::string line;
    	std::string cell[4];

    	while (std::getline(data, line)) {
    		std::stringstream linestream(line);
    		std::getline(linestream, cell[0], ',');
    		std::getline(linestream, cell[1], ',');
    		std::getline(linestream, cell[2], ',');
    		std::getline(linestream, cell[3], ',');
    		CSV *linha = new CSV(cell[0], cell[1] ,cell[2], cell[3]);
    		CSVvector.push_back(linha);
    		this->Total_lines++;
    	}

    }

    CSV* get_line(int line_number){

    	return CSVvector.at(line_number-1);
    }


    int getTotalLines( void ){
    	return Total_lines;
    }


};


//todo -->> metodo para liberar memória
class Application {

   	 private:

		std::string project_name;
		std::string project_file;
		std::string code_file;
		CSV_Editor *CSV_editor;

    public:

	std::mutex mtx;

    Application(){
    	this->CSV_editor = new CSV_Editor();
    	this->project_file = "";
    	this->project_name = "";
    	this->code_file = "";
    }

//	void generate_code();

    void new_project(std::string project_name, std::string project_file){

    	this->project_name = project_name;
    	this->project_file = project_file;
    	CSV_editor->insert_line("project_title", "text",project_file, project_name);
    	CSV_editor->insert_line("set", "text","web_page_name", "");
    	CSV_editor->insert_line("set", "text","page_title", "");
    	this->save_project();
    }

    bool load_project(std::string project_file_name){


    	CSV_editor->load_project(project_file_name);
    	CSV *title = CSV_editor->get_line(1);
    	this->project_name = title->getName();
    	this->project_file = title->getLabel();


    }
    bool save_project(void){
    	return CSV_editor->save_project(this->project_file);
    }

    CSV_Editor* get_CSVeditor( void ){

    	return this->CSV_editor;
    }

    std::string get_ProjectName(void){
    	return this->project_name;
    }

    std::string get_ProjectFile(void){
        	return this->project_file;
     }
};

class Radio {

private:

	std::string Label;
	std::string Name;
	std::vector<std::string> Radio_buttons;

public:

	Radio(std::string Label, std::string Name){

		this->Label = Label;
		this->Name = Name;

	}
	std::string getLabel( void ){
		return Label;
	}

	std::string getName( void ){
			return Name;
	}

	void insert_RadioButton( std::string button ){

		Radio_buttons.push_back(button);
	}

	std::vector<std::string> Get_Radio_buttons( void ){

		return Radio_buttons;
	}


};

// todo -->> metodo para liberar memoria
class Code_Generator {

private:

	std::string project_title;
	std::string web_page_name;
	std::vector<CSV*> adds;
	std::string snippets[7];

    std::vector<CSV*> CSVvector;
    std::ofstream CSV_file;
    std::ofstream HTML_file;

    std::vector<Radio*> Radio_adds;


public:

    Code_Generator(std::string project_title, std::string web_page_name, std::string CSV_file_name){

    	this->snippets[0] = "<!--DO NOT EDIT THIS FILE BY HAND-->\n"
    			"<!DOCTYPE html>\n"
    			"<html lang=\"en\">\n"
    			"<head>\n"
    			"    <meta charset=\"utf-8\">\n"
    			"    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
    			"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";


    	this->snippets[1] = "    <link href=\"css/bootstrap.min.css\" rel=\"stylesheet\" media=\"screen\">\n"
    			"    <script language=\"JavaScript\" type=\"text/javascript\" src=\"js/jquery-1.11.1.min.js\"></script>\n"
    			"    <script language=\"JavaScript\" type=\"text/javascript\" src=\"js/bootstrap-3.1.1.min.js\"></script>\n"
    			"    <script language=\"JavaScript\" type=\"text/javascript\" src=\"js/jquery.validationEngine-2.6.2.js\"></script>\n"
    			"    <script language=\"JavaScript\" type=\"text/javascript\" src=\"js/jquery.validationEngine-en.js\"></script>\n"
    			"    <link href=\"css/validationEngine.jquery.css\" rel=\"stylesheet\" media=\"screen\">\n"
    			"    <script language=\"JavaScript\" type=\"text/javascript\" src=\"js/jquery.dataTables-1.10.0.min.js\"></script>\n"
    			"    <link href=\"css/jquery.dataTables.min.css\" rel=\"stylesheet\" media=\"screen\">\n"
    			"</head>\n"
    			"<body>\n"
    			"    <div class=\"container\">\n";

    	this-> snippets[2] = "    \t<div id=\"list\">\n"
    			"    \t\t<table id=\"table\" class=\"display\"></table>\n"
    			"    \t\t<div class=\"form-group\">\n"
    			"    \t\t\t<button type=\"submit\" class=\"submit btn btn-primary\" id=\"add\">Add</button>\n"
    			"    \t\t</div>\n"
    			"\t    </div>\n"
    			"    \t<form class=\"form-horizontal\" role=\"form\" id=\"formID\">\n"
    			"    \t\t<div class=\"form-group\">\n"
    			"    \t\t\t<label for=\"seq\" class=\"col-sm-2 control-label\">Id</label>\n"
    			"    \t\t\t<div class=\"col-sm-6\">\n"
    			"    \t\t\t\t<p class=\"form-control-static\" id=\"seq\"></p>\n"
    			"    \t\t\t</div>\n"
    			"    \t\t</div>\n";

    	this-> snippets[3] = "    \t\t<div class=\"form-group\">\n"
    			"    \t\t\t<div class=\"col-sm-offset-2 col-sm-8\">\n"
    			"    \t\t\t\t<button class=\"btn btn-default\" id=\"cancel\">Cancel</button>\n"
    			"    \t\t\t\t<button type=\"submit\" class=\"submit btn btn-primary\" id=\"save\">Save</button>\n"
    			"    \t\t\t</div>\n"
    			"    \t\t</div>\n"
    			"    \t</form>\n"
    			"\t</div>\n"
    			"</body>\n"
    			"<script>\n"
    			"\tvar editor; // use a global for the submit and return data rendering in the examples\n"
    			"\tvar formId=\"sample\";\n"
    			"\tvar oTable;\n"
    			"\t$(document).ready(function(){\n"
    			"\t\t$('#formID').hide();\n"
    			"\t\tvar seq=createTable();\n"
    			"\t\t$('#seq').text(seq);\n"
    			"\t\t$(\"#formID\").validationEngine(\'attach\',\n"
    			"\t\t{\n"
    			"\t\t\tonValidationComplete: function(form, status){\n"
    			"\t\t\t\tif (!verifyLocalStorageCapability) {\n"
    			"\t\t\t\t\talert(\"Local Storage is not supported.\");\n"
    			"\t\t\t\t\treturn;\n"
    			"\t\t\t\t}\n"
    			"\t\t\t\tif (status) {\n"
    			"\t\t\t\t\tsave();\n"
    			"\t\t\t\t\tlocation.reload(true);\n"
    			"\t\t\t\t}\n"
    			"\t\t\t}\n"
    			"\t\t});\n"
    			"\t});\n"
    			"\n"
    			"\tfunction createTable() {\n"
    			"\t\tvar dataSet=[];\n"
    			"\t\tvar skip=0;\n"
    			"\t\tvar seq=0;\n"
    			"\t\tvar index=0;\n"
    			"\t\tvar icons  =\'<span class=\"glyphicon glyphicon-edit\">&nbsp;</span><span class=\"glyphicon glyphicon-remove\"></span>\';\n"
    			"\n"
    			"\t\twhile ( skip<2 ) {\n"
    			"\t\t\tvar key=formId+\"_\"+index;\n"
    			"\t\t\tvar json=localStorage.getItem(key);\n"
    			"\t\t\tif ( json==null || json==\"null\" || json==\"[object Object]\" ) {\n"
    			"\t\t\t\tindex=index+1;\n"
    			"\t\t\t\tskip=skip+1;\n"
    			"\t\t\t\tcontinue;\n"
    			"\t\t\t}\n"
    			"\t\t\tvar object=null;\n"
    			"\t\t\tobject=JSON.parse(json);\n"
    			"//\t\t\tvar note= object.note;\n"
    			"//\t\t\tnote=note.replace(/\\n/g, \"<br>\");\n";

    	this->snippets[4] = 	"\t\t\tindex=index+1;\n"
    			"\t\t\tseq=seq+1;\n"
    			"\t\t}\n"
    			"\n"
    			"oTable=$('#table').dataTable({\n"
    			"\"data\": dataSet,\n"
    			"\"columns\": [\n"
    			"{ \"title\": \"Seq\", \"class\": \"center\" },\n"
    			"{ \"title\": \"\", \"class\": \"center\" },\n";

    	this->snippets[5] = "\t\t$('#table tbody').on( 'click', '.glyphicon-remove', function () {\n"
				"\t\t    var row = $(this).parents('tr');\n"
				"\t\t    var seq = row.children()[0].innerHTML;\n"
				"\t\t    if(window.confirm('Are you sure to delete? Seq='+seq)){\n"
				"\t\t    \tvar key=formId+\"_\"+seq;\n"
				"\t\t    \tlocalStorage.removeItem(key);\n"
				"\t\t    \trestoreItems();\n"
				"        \tlocation.reload(true);\n"
				"\t\t    }\n"
				"\t\t} );\n"
				"\n"
				"\t\t$('#add').on( 'click', function () {\n"
				"\t\t    $('#list').hide();\n"
				"\t\t    $('#seq').text(seq);\n"
				"\t\t    $('#formID').show();\n"
				"\t\t} );\n"
				"\n"
				"\t\t$('#cancel').on( 'click', function () {\n"
				"\t\t    location.reload(true);\n"
				"\t\t} );\n"
				"\n"
				"$('#table tbody').on( 'click', '.glyphicon-edit', function () {\n"
				"$('#list').hide();\n"
				"var rows = $(this).parents('tr').children();\n"
				"$('#seq').text(rows[0].innerHTML);\n";

    	this->snippets[6] =  "\tfunction restoreItems() {\n"
    			"\t\tvar skip=0;\n"
    			"\t\tvar index=1;\n"
    			"\t\tvar previous=JSON.parse(localStorage.getItem(formId+\"_0\"));\n"
    			"\t\tvar prevIndex=0;\n"
    			"\t\twhile ( skip<2 ) {\n"
    			"\t\t\tvar key=formId+\"_\"+index;\n"
    			"\t\t\tvar object=JSON.parse(localStorage.getItem(key));\n"
    			"\t\t\tif ( previous==null && object==null ) {\n"
    			"\t\t\t\tskip=skip+1;\n"
    			"\t\t\t\tprevIndex=index;\n"
    			"\t\t\t\tindex=index+1;\n"
    			"\t\t\t\tcontinue;\n"
    			"\t\t\t}\n"
    			"\t\t\tif ( previous==null && object!=null ) {\n"
    			"\t\t\t\tlocalStorage.setItem(formId+\"_\"+prevIndex, JSON.stringify(object));\n"
    			"\t\t\t\tlocalStorage.setItem(key, null);\n"
    			"\t\t\t\tprevIndex=index;\n"
    			"\t\t\t\tindex=index+1;\n"
    			"\t\t\t\tcontinue;\n"
    			"\t\t\t}\n"
    			"\t\t\tprevious=object;\n"
    			"\t\t\tprevIndex=index;\n"
    			"\t\t\tindex=index+1;\n"
    			"\t\t}\n"
    			"\t};\n"
    			"\n"
    			"\n"
    			"\tfunction verifyLocalStorageCapability() {\n"
    			"\t\tif (!window.localStorage) {\n"
    			"\t    \treturn false;\n"
    			"\t\t}\n"
    			"\t\treturn true;\n"
    			"\t}\n"
    			"</script>\n"
    			"</html>\n"
    			"\n";

    	this->project_title = project_title;
    	this->web_page_name = web_page_name;
    	this->load_project(CSV_file_name);
    	this->fill_adds();


    }

    // todo excessões
    void fill_adds( void ){

           for (auto i = (CSVvector.begin()+3); i != CSVvector.end(); i++){

        	   if ((*i)->getCommand() == "add" && (*i)->getType() == "text"){
            	   adds.push_back((*i));
               }

        	   if ((*i)->getCommand() == "add" && (*i)->getType() == "radio"){
            	   //adds.push_back((*i));

        		   Radio* button = new Radio((*i)->getLabel(), (*i)->getName());

        		   i++;
        		   while(i != CSVvector.end() && (*i)->getCommand() == "radio_bt"){

        			   if((*i)->getType() != "#null#"){
        				   button->insert_RadioButton((*i)->getType());
        			   }
        			   if((*i)->getLabel() != "#null#"){
        				   button->insert_RadioButton((*i)->getLabel());
        			   }
        			   if((*i)->getName() != "#null#"){
        				   button->insert_RadioButton((*i)->getName());
        			   }
        			   i++;
        		   }

        		   Radio_adds.push_back(button);
        		   i--;
               }
           }
    }

    bool write_code(){

    	HTML_file.open("HTML/index.html");
    	if(!HTML_file.is_open()){
    		return false;
    	}


    	//WEB PAGE NAME
    	HTML_file << snippets[0];
    	HTML_file << "<title>" << this->web_page_name << "</title>\n";

    	//PAGE TITLE
    	HTML_file << snippets[1];
    	HTML_file << "<h1>" << this->project_title << "</h1>\n";

    	//INSERT ADDS
    	HTML_file << snippets[2];

    	for (auto i = adds.begin(); i != adds.end(); i++){

    		HTML_file << "<div class=\"form-group\">\n";
    		HTML_file << "<label for=\"" << (*i)->getLabel() << "\" class=\"col-sm-2 control-label\">" << (*i)->getName() << "</label>\n";
    		HTML_file << "<div class=\"col-sm-6\">\n";
    		HTML_file << "<input type=\"" << (*i)->getType() << "\" class=\"form-control validate[required]\" id=\"" << (*i)->getLabel() << "\" placeholder=\"" << (*i)->getName() << "\">\n";
    		HTML_file << "</div>\n";
    		HTML_file << "</div>\n";

    	}

    	int rvar = 0;
      	for (auto i = Radio_adds.begin(); i != Radio_adds.end(); i++){

//        		std::cout<< "RADIO(" << (*i)->getLabel() << ", " << (*i)->getName() << ")" << std::endl;
        		auto vec = (*i)->Get_Radio_buttons();

        	 	HTML_file << "    \t\t<div class=\"form-group\">\n";
        	 	HTML_file << "    \t\t\t<label for=\"" << (*i)->getLabel() << "\" class=\"col-sm-2 control-label\">" << (*i)->getName() << "</label>\n";

        	    HTML_file <<	"    \t\t\t<div class=\"col-sm-6\">\n";

        		for (auto a = vec.begin(); a != vec.end(); a++){

//        			std::cout << "\t" << (*a) << std::endl;

        			HTML_file << "\t    \t\t\t<div class=\"radio\">\n"
        		    	"\t    \t\t\t\t<label>\n";

        			std::string var;
        			var = (*a);
        			delSpaces(var);
        		    HTML_file <<	"\t    \t\t\t\t\t<input type=\"radio\" class=\"validate[required]\" name=\"" << (*i)->getLabel() << "\" value=\"" << var <<"\">\n"
        		    	"\t    \t\t\t\t\t" << (*a) << "\n";
        		    rvar++;

        		    HTML_file <<	"\t    \t\t\t\t</label>\n"
        		    	"\t    \t\t\t</div>\n";
        		}

        		HTML_file <<  "    \t\t\t</div>\n"
        		    	"    \t\t</div>\n";


        }

    	HTML_file << snippets[3];

    	HTML_file << "dataSet[seq]=[index, icons";
    	for (auto i = adds.begin(); i != adds.end(); i++){

    		HTML_file << ", object." << (*i)->getLabel();

        }

    	for (auto i = Radio_adds.begin(); i != Radio_adds.end(); i++){

    		HTML_file << ", object." << (*i)->getLabel();

    	}

    	HTML_file << "];\n";

        HTML_file << snippets[4];

    	for (auto i = adds.begin(); i != adds.end(); i++){

    		HTML_file << "{ \"title\": \"" << (*i)->getName() << "\"},\n";

        }

        for (auto i = Radio_adds.begin(); i != Radio_adds.end(); i++){

        	HTML_file << "{ \"title\": \"" << (*i)->getName() << "\"},\n";
        }

        HTML_file << "]\n" << "});\n";

        HTML_file << snippets[5];

        int count = 2;
    	for (auto i = adds.begin(); i != adds.end(); i++){

        		HTML_file << "$('#" << (*i)->getLabel() << "').val(rows[" << count << "].innerHTML);\n";
        		count++;
         }

    	for (auto i = Radio_adds.begin(); i != Radio_adds.end(); i++){

    		HTML_file << "$('input[name=\"" << (*i)->getLabel() << "\"]').val([rows[" << count << "].innerHTML]);\n";
    		count++;
    	}


    	HTML_file << "$('#formID').show();\n" << "} );\n" << "\n";


    	HTML_file << "\n"
    			"\t\treturn seq;\n"
    			"\t}\n"
    			"\n"
    			"function save() {\n"
				"  var seq=$('#seq').text();\n"
				"  if ( isNaN(seq) ) { seq=0; }\n"
				"  var key=formId+\"_\"+seq;\n"
				"  var object={\n";

    	for (auto i = adds.begin(); i != adds.end(); i++){

    		HTML_file << "\"" << (*i)->getLabel() << "\": $(\"#" << (*i)->getLabel() << "\").val(),\n";
    	}

    	for (auto i = Radio_adds.begin(); i != Radio_adds.end(); i++){

    		HTML_file << "\"" << (*i)->getLabel() << "\": $('input[name=\"" << (*i)->getLabel() << "\"]:checked').val(),\n";
    	}


    	HTML_file << "}\n"
				"localStorage.setItem(key, JSON.stringify(object));\n"
				"}\n";


    	HTML_file << snippets[6];


    	HTML_file.close();
    	return true;

    }

    bool write_project(std::string file_name){

    	CSV_file.open(file_name.data());
    	if(!CSV_file.is_open()){
    		return false;
    	}

    	for (auto i = CSVvector.begin(); i != CSVvector.end(); i++){
    		//CSV *teste = i;
    		CSV_file << (*i)->getCommand() << "," << (*i)->getType()<< "," << (*i)->getLabel()<< "," << (*i)->getName() << std::endl;

    	}

    	CSV_file.close();
    	return true;
    }

//    void print_radio_adds( void ){
//
//    	for (auto i = Radio_adds.begin(); i != Radio_adds.end(); i++){
//
//    		std::cout<< "RADIO(" << (*i)->getLabel() << ", " << (*i)->getName() << ")" << std::endl;
//    		auto vec = (*i)->Get_Radio_buttons();
//
//    		for (auto a = vec.begin(); a != vec.end(); a++){
//
//    			std::cout << "\t" << (*a) << std::endl;
//    		}
//
//    	}
//    }


    //todo
//    void page_title_writer(line){
//
//
//    }


    bool load_project(std::string file_name){

    	//todo verificar se arquivo está correto.
    	//todo salvar nome do projeto e nome do arquivo

    	std::vector<CSV*> novo;
    	std::ifstream data(file_name.data());

    	std::string line;
    	std::string cell[4];

    	while (std::getline(data, line)) {
    		std::stringstream linestream(line);
    		std::getline(linestream, cell[0], ',');
    		std::getline(linestream, cell[1], ',');
    		std::getline(linestream, cell[2], ',');
    		std::getline(linestream, cell[3], ',');
    		CSV *linha = new CSV(cell[0], cell[1] ,cell[2], cell[3]);
    		novo.push_back(linha);
    		this->CSVvector = novo;
    	}


    }

};

class Data {
private:

	std::string nome_posto;
	float preco;
	std::string tipo_combustivel;

public:
  Data(std::string nome_posto, float preco, std::string tipo_combustivel) {
    this->nome_posto = nome_posto;
    this->preco = preco;
    this->tipo_combustivel = tipo_combustivel;
  }
  float getPreco() {
    return preco;
  }
  std::string getPosto() {
    return nome_posto;
  }
  std::string getCombustivel() {
     return tipo_combustivel;
   }
  void setPosto(std::string name) {
    this->nome_posto = name;
  }  
  void setCombustivel(std::string comb) {
      this->tipo_combustivel = comb;
    }
  void setPreco(float preco) {
    this->preco = preco;
  }  

};


class View : public UserInterface {

private:
  std::vector<Data> data; 
  Application *app;
   
public:
  
  View() {

	this->hide_project_settings();

    btnClear->callback((Fl_Callback*) cbBtnClear, (void*)(this));
    btnUpdate->callback((Fl_Callback*) cbBtnUpdate, (void*)(this)); 
    btnDelete->callback((Fl_Callback*) cbBtnDelete, (void*)(this)); 
    btnInsert->callback((Fl_Callback*) cbBtnInsert, (void*)(this)); 
    browser->callback((Fl_Callback*) cbBrowser, (void*)(this));

    //New and Load Project
    LoadProject->callback((Fl_Callback*) cbLoadProject, (void*)(this));
    NewProject->callback((Fl_Callback*) cbNewProject, (void*)(this));
    New_Pro_OK_bt->callback((Fl_Callback*) cbNewProject_OK_bt, (void*)(this));
    New_Pro_Cancel_bt->callback((Fl_Callback*) cbNewProject_Cancel_bt, (void*)(this));

    //Radio_bt callbacks
    Radio_Update_bt->callback((Fl_Callback*) cbRadio_Update_bt, (void*)(this));
    Radio_cancel_bt->callback((Fl_Callback*) cbRadio_Cancel_bt, (void*)(this));
    Insert_Radio_bt->callback((Fl_Callback*) cbInsert_Radio_bt, (void*)(this));
    insert_bt_Radio->callback((Fl_Callback*) cbInsert_bt_Radio, (void*)(this));

    //Code Generator
    Generate_Code_bt->callback((Fl_Callback*) cbGenerate_Code_bt, (void*)(this));

    //Set Title
    Set_title->callback((Fl_Callback*) cbSet_title, (void*)(this));
    Title_save_bt->callback((Fl_Callback*) cbTitle_save_bt, (void*)(this));
    Title_cancel_bt->callback((Fl_Callback*) cbTitle_cancel_bt, (void*)(this));


    this->app= new Application();
    insert_bt_Radio->hide();
  }
  
  void hide_project_settings(void){


	  this->inputLabel->hide();
	  this->inputName->hide();
	  this->chooser->hide();
	  this->browser->hide();
	  this->btnClear->hide();
	  this->btnDelete->hide();
	  this->btnInsert->hide();
	  this->btnUpdate->hide();
	  this->Title_Project->hide();
  }

  void show_project_settings(void){


	  this->inputLabel->show();
	  this->inputName->show();
	  this->chooser->show();
	  this->browser->show();
	  this->btnClear->show();
	  this->btnDelete->show();
	  this->btnInsert->show();
	  this->btnUpdate->show();
	  this->Title_Project->show();
  }

  void show() {
    // Mostra janela
    w->show();
  }
  
  // Funcao callback chamada quando pressionado botao 'Clear'
  static void cbBtnClear(Fl_Widget* btn, void* userdata) {
    View* gui = static_cast<View*>(userdata);
    gui->inputLabel->value("");
    gui->inputName->value("");
  }

  // Funcao callback chamada quando pressionado botao 'Insert'
  static void cbBtnInsert(Fl_Widget* btn, void* userdata) {
    View* gui = static_cast<View*>(userdata);

    std::string Label_str(gui->inputLabel->value());
    std::string Name_str(gui->inputName->value());
    std::string add = "add";
    std::string text = "text";
    std::string radio = "radio";

    if(Label_str != "" && Name_str != ""){
    	int type = gui->chooser->value();
    	std::string type_str;
    	switch(type){
    	case 0: {

    		type_str = "text";
    		Application* a = gui->app;
    		(a->get_CSVeditor())->insert_line(add, text, Label_str, Name_str);
    		gui->browser->add((add + ": " + text + " : " + " : " + Label_str + " : " + Name_str).c_str());
    		a->save_project();

    		break;

    	}
    	case 1: {

    		type_str = "radio";
    		Application* a = gui->app;
    		(a->get_CSVeditor())->insert_line(add, radio, Label_str, Name_str);
    		gui->browser->add((add + ": " + radio + " : " + " : " + Label_str + " : " + Name_str).c_str());
    		a->save_project();
    		break;

    	}
    	}


    } else fl_alert("Please, insert Label and Name values.");

  }

  // Funcao callback chamada quando selecionada uma linha no Fl_Browser
  static void cbBrowser(Fl_Widget* btn, void* userdata) {
    View* gui = static_cast<View*>(userdata);
    int index = gui->browser->value(); // 1-based index

    if(index != 0){

    	CSV* line = gui->app->get_CSVeditor()->get_line(index);

    	gui->inputLabel->value(line->getLabel().c_str());
    	gui->inputName->value(line->getName().c_str());

    	if(line->getType() == "text"){
    		gui->chooser->value(0);
    	}
    	else if(line->getType() == "radio"){
    		gui->chooser->value(1);
    	}

    	if(line->getCommand() == "radio_bt"){

    		gui->Radio_bt_Window->show();
    		gui->Radio_bt_1->value(line->getType().c_str());
    		gui->Radio_bt_2->value(line->getLabel().c_str());
    		gui->Radio_bt_3->value(line->getName().c_str());

    	}


    }
//    std::cout << "LINHA: " << index << std::endl;


  }

  // Funcao callback chamada quando pressionado botao 'Update'
  static void cbBtnUpdate(Fl_Widget* btn, void* userdata) {
	  View* gui = static_cast<View*>(userdata);
	  int index = gui->browser->value(); // 1-based index
	  if (index != 0 && index > 3) {

	    std::string Label_str(gui->inputLabel->value());
	    std::string Name_str(gui->inputName->value());
	    std::string add = "add";
	    std::string text = "text";
	    std::string radio = "radio";

	    if(Label_str != "" && Name_str != ""){
	    	int type = gui->chooser->value();
	    	std::string type_str;
	    	switch(type){
	    	case 0: {

	    		type_str = "text";
	    		Application* a = gui->app;
	    		(a->get_CSVeditor())->edit_entire_line(index, add, text, Label_str, Name_str);
	    		gui->browser->remove(index);
	    		gui->browser->insert(index, (add + ": " + text + " : " + " : " + Label_str + " : " + Name_str).c_str());
	    		a->save_project();

	    		break;

	    	}
	    	case 1: {

	    		type_str = "radio";
	    		Application* a = gui->app;
	    		(a->get_CSVeditor())->edit_entire_line(index, add, radio, Label_str, Name_str);
	    		gui->browser->remove(index);
	    		gui->browser->insert(index, (add + ": " + radio + " : " + " : " + Label_str + " : " + Name_str).c_str());
	    		a->save_project();
	    		break;

	    	}
	    	}


	    } else fl_alert("Please, insert Label and Name values.");

	  }
	  if (index != 0 && index < 4){

			  fl_alert("Lines 1, 2, 3 can not be edit.");
		  }

  }

  // Funcao callback chamada quando pressionado botao 'Delete'
  static void cbBtnDelete(Fl_Widget* btn, void* userdata) {
	  View* gui = static_cast<View*>(userdata);
	  int index = gui->browser->value(); // 1-based index
	  if (index > 3) {

		  gui->app->get_CSVeditor()->delete_line(index);
		  gui->browser->remove(index);
		  gui->app->save_project();
	  }

	  if (index != 0 && index < 4){

		  fl_alert("Lines 1, 2, 3 can not be delete.");
	  }
  }



  // Funcao callback chamada quando pressionado botao 'Load Project'
   static void cbLoadProject(Fl_Widget* btn, void* userdata) {

	 View* gui = static_cast<View*>(userdata);
     Fl_File_Chooser* fc = new Fl_File_Chooser(".","CSV Files (*.{csv})",Fl_File_Chooser::SINGLE,"File Browser");

     fc->show();
     while(fc->shown()) Fl::wait();

     if(fc->value() != nullptr){
    	 std::string filename = fc->value();
    	 std::cout << filename << "\n";
 		gui->app->load_project(filename);
// 		std::cout << ">> In Project \"" << gui->app->get_ProjectName() << "\", file loaded: OK." << std::endl;
 		gui->Title_Project->value(gui->app->get_ProjectName().c_str());
 		gui->show_project_settings();
     }

     CSV_Editor* editor = gui->app->get_CSVeditor();

     for(auto i = 1 ; i <= editor->getTotalLines(); i++){

    	 CSV* line = editor->get_line(i);
    	 gui->browser->add((line->getCommand()+" : "+line->getType()+" : "+line->getLabel()+" : "+line->getName()).c_str());
     }



   }

   static void cbNewProject(Fl_Widget* btn, void* userdata) {

	   View* gui = static_cast<View*>(userdata);
	   gui->NewProjectWindow->show();


   }

   static void cbNewProject_OK_bt(Fl_Widget* btn, void* userdata) {

	   View* gui = static_cast<View*>(userdata);
	   std::string project_name = gui->ProjectName_input->value();
	   std::string project_file = gui->ProjectFile_input->value();
	   gui->app->new_project(project_name, project_file);

	   std::cout << project_name << " E " << project_file << std::endl;
	   gui->NewProjectWindow->hide();
	   gui->show_project_settings();
	   gui->Title_Project->value(gui->app->get_ProjectName().c_str());

	   CSV_Editor* editor = gui->app->get_CSVeditor();

	     for(auto i = 1 ; i <= editor->getTotalLines(); i++){

	    	 CSV* line = editor->get_line(i);
	    	 gui->browser->add((line->getCommand()+" : "+line->getType()+" : "+line->getLabel()+" : "+line->getName()).c_str());
	     }

   }

   static void cbNewProject_Cancel_bt(Fl_Widget* btn, void* userdata) {

	   View* gui = static_cast<View*>(userdata);
	   gui->NewProjectWindow->hide();

   }

   static void cbRadio_Update_bt(Fl_Widget* btn, void* userdata) {

	   View* gui = static_cast<View*>(userdata);
	   int index = gui->browser->value(); // 1-based index
	   std::string radio_bt = "radio_bt";

	   if (index != 0){

			Application* a = gui->app;
			(a->get_CSVeditor())->edit_entire_line(index, "radio_bt", gui->Radio_bt_1->value(), gui->Radio_bt_2->value(), gui->Radio_bt_3->value());
			gui->browser->remove(index);
	 		gui->browser->insert(index, (radio_bt + ": " + gui->Radio_bt_1->value() + " : " + gui->Radio_bt_2->value() + " : " + gui->Radio_bt_3->value()).c_str());

	   }

	   gui->app->save_project();
	   gui->Radio_bt_Window->hide();


   }

   static void cbRadio_Cancel_bt(Fl_Widget* btn, void* userdata) {

	   View* gui = static_cast<View*>(userdata);
	   gui->Radio_bt_Window->hide();

   }


   static void cbGenerate_Code_bt(Fl_Widget* btn, void* userdata) {

	   View* gui = static_cast<View*>(userdata);

	   CSV_Editor* editor = gui->app->get_CSVeditor();
	   Code_Generator code(editor->get_PageTitle(), editor->get_WebPage_name(), gui->app->get_ProjectFile());
	   code.write_code();



   }

   static void cbSet_title(Fl_Widget* btn, void* userdata) {

	   View* gui = static_cast<View*>(userdata);
	   gui->Title_window->show();
   }

//   cbTitle_save_bt

   static void cbTitle_save_bt(Fl_Widget* btn, void* userdata) {

	   View* gui = static_cast<View*>(userdata);

	   std::string set = "set";
	   std::string text = "text";
	   std::string label1 = "web_page_name";
	   std::string label2 = "page_title";


	   std::string Web_pg_name = gui->Web_page_name->value();
	   std::string Web_pg_title = gui->Web_page_title->value();

	   gui->app->get_CSVeditor()->edit_line_element(2, 4, Web_pg_name);
	   gui->app->get_CSVeditor()->edit_line_element(3, 4, Web_pg_title);

	   gui->browser->remove(2);
	   gui->browser->insert(2, (set + ": " + text + " : " + label1 + " : " + Web_pg_name).c_str());

	   gui->browser->remove(3);
	   gui->browser->insert(3, (set + ": " + text + " : " + label2 + " : " + Web_pg_title).c_str());

	   gui->app->save_project();


	   gui->Title_window->hide();
   }

   static void cbTitle_cancel_bt(Fl_Widget* btn, void* userdata) {

	   View* gui = static_cast<View*>(userdata);
	   gui->Title_window->hide();
   }


   static void cbInsert_Radio_bt(Fl_Widget* btn, void* userdata) {

	   View* gui = static_cast<View*>(userdata);
	   gui->Radio_bt_Window->show();
	   gui->insert_bt_Radio->show();
   }

   static void cbInsert_bt_Radio(Fl_Widget* btn, void* userdata) {

	   View* gui = static_cast<View*>(userdata);
	   std::string radio_bt = "radio_bt";

	   gui->Radio_bt_1->value("#null#");
	   gui->Radio_bt_2->value("#null#");
	   gui->Radio_bt_3->value("#null#");


	   Application* a = gui->app;
	   (a->get_CSVeditor())->insert_line("radio_bt", gui->Radio_bt_1->value(), gui->Radio_bt_2->value(), gui->Radio_bt_3->value());
	   gui->browser->add((radio_bt + ": " + gui->Radio_bt_1->value() + " : " + gui->Radio_bt_2->value() + " : " + gui->Radio_bt_3->value()).c_str());
	   gui->app->save_project();

	   gui->insert_bt_Radio->hide();
	   gui->Radio_bt_Window->hide();

   }



};

int main() {
  View gui;
  gui.show();
  return Fl::run();
}


