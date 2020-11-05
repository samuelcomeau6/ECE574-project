#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "path.h"
#include "data_list.h"
#include "data_type.h"

using namespace std;

int TopSort(data_list Graph, data_list List, data_type vertex) {

	for (int i = 0; Graph.data_v.size(); i++) {

		Graph.data_v[i].color = "White";
		TopSortVisit(Graph, List, Graph.data_v[i]);

	}
}

int TopSortVisit(data_list Graph, data_list List, data_type uVertex) {


	uVertex.color = "Gray";
	for (int i = 0; Graph.data_v.size(); i++) {

		if (uVertex.output_name == Graph.data_v[i].input_1_name || uVertex.output_name == Graph.data_v[i].input_2_name) {

			if (Graph.data_v[i].color == "White" && Graph.data_v[i].operation_name != "REG") {
				TopSortVisit(Graph, List, Graph.data_v[i]);
			}
			else if (Graph.data_v[i].color == "White" && Graph.data_v[i].operation_name == "REG") {
				Graph.data_v[i].color = "Black";
				List.data_v.push_back(Graph.data_v[i]);
			}
			Graph.data_v[i].color = "Black";
			List.data_v.push_back(Graph.data_v[i]);
		}
	}
}


int LongestPath(data_list Graph) {

	int max = 0;
	float pathDur = 0;
	float critPathDur = 0;
	data_list List;
	vector<float> pathDurStor;

	for (int i = 0; Graph.data_v.size(); i++) {

		TopSort(Graph, List, Graph.data_v[i]);

		for (int i = 0; List.data_v.size(); i++) {

			if ((List.data_v[i].operation_name == "REG" && (Graph.data_v[i] == List.data_v[i]))||(Graph.data_v[i].operation_name != "REG")) {
				if (List.data_v[i].duration > pathDur) {
					pathDur = List.data_v[i].duration + pathDur;
				}
			}
		}
		pathDurStor.push_back(pathDur);
		pathDur = 0;
	}

	critPathDur = *max_element(pathDurStor.begin(), pathDurStor.end());
}



int assignDuration(data_list Graph) {

	for (int i = 0; i < Graph.data_v.size(); i++) {

		//Register duration Assignment
		if (Graph.data_v[i].operation_name == "REG") {
			if (Graph.data_v[i].width == 1) {
				Graph.data_v[i].duration = 2.616;
			}
			else if (Graph.data_v[i].width == 2) {
				Graph.data_v[i].duration = 2.644;
			}
			else if (Graph.data_v[i].width == 8) {
				Graph.data_v[i].duration = 2.879;
			}
			else if (Graph.data_v[i].width == 16) {
				Graph.data_v[i].duration = 3.061;
			}
			else if (Graph.data_v[i].width == 32) {
				Graph.data_v[i].duration = 3.602;
			}
			else if (Graph.data_v[i].width == 64) {
				Graph.data_v[i].duration = 3.966;
			}
			else {
				printf("Invalid REG Size");
			}
		}
		//case parse::ADD:     output = "ADD"; break;

		//Add duration Assignment
		if (Graph.data_v[i].operation_name == "ADD") {
			if (Graph.data_v[i].width == 1) {
				Graph.data_v[i].duration = 2.704;
			}
			else if (Graph.data_v[i].width == 2) {
				Graph.data_v[i].duration = 3.713;
			}
			else if (Graph.data_v[i].width == 8) {
				Graph.data_v[i].duration = 4.924;
			}
			else if (Graph.data_v[i].width == 16) {
				Graph.data_v[i].duration = 5.638;
			}
			else if (Graph.data_v[i].width == 32) {
				Graph.data_v[i].duration = 7.270;
			}
			else if (Graph.data_v[i].width == 64) {
				Graph.data_v[i].duration = 9.566;
			}
			else {
				printf("Invalid ADD Size");
			}
		}
		//case parse::SUB:     output = "SUB"; break;
		//Subtractor duration Assignment
		if (Graph.data_v[i].operation_name == "SUB") {
			if (Graph.data_v[i].width == 1) {
				Graph.data_v[i].duration = 3.024;
			}
			else if (Graph.data_v[i].width == 2) {
				Graph.data_v[i].duration = 3.412;
			}
			else if (Graph.data_v[i].width == 8) {
				Graph.data_v[i].duration = 4.890;
			}
			else if (Graph.data_v[i].width == 16) {
				Graph.data_v[i].duration = 5.569;
			}
			else if (Graph.data_v[i].width == 32) {
				Graph.data_v[i].duration = 7.253;
			}
			else if (Graph.data_v[i].width == 64) {
				Graph.data_v[i].duration = 9.566;
			}
			else {
				printf("Invalid SUB Size");
			}
		}
		//case parse::MUL:     output = "MUL"; break;
		//Mul duration Assignment
		if (Graph.data_v[i].operation_name == "MUL") {
			if (Graph.data_v[i].width == 1) {
				Graph.data_v[i].duration = 2.438;
			}
			else if (Graph.data_v[i].width == 2) {
				Graph.data_v[i].duration = 3.651;
			}
			else if (Graph.data_v[i].width == 8) {
				Graph.data_v[i].duration = 7.453;
			}
			else if (Graph.data_v[i].width == 16) {
				Graph.data_v[i].duration = 7.811;
			}
			else if (Graph.data_v[i].width == 32) {
				Graph.data_v[i].duration = 12.395;
			}
			else if (Graph.data_v[i].width == 64) {
				Graph.data_v[i].duration = 15.354;
			}
			else {
				printf("Invalid MUL Size");
			}
		}
		//case parse::COMPLT:  output = "COMP<"; break;
		//COMP duration Assignment
		if (Graph.data_v[i].operation_name == "COMPLT") {
			if (Graph.data_v[i].width == 1) {
				Graph.data_v[i].duration = 3.031;
			}
			else if (Graph.data_v[i].width == 2) {
				Graph.data_v[i].duration = 3.934;
			}
			else if (Graph.data_v[i].width == 8) {
				Graph.data_v[i].duration = 5.949;
			}
			else if (Graph.data_v[i].width == 16) {
				Graph.data_v[i].duration = 6.256;
			}
			else if (Graph.data_v[i].width == 32) {
				Graph.data_v[i].duration = 7.264;
			}
			else if (Graph.data_v[i].width == 64) {
				Graph.data_v[i].duration = 8.416;
			}
			else {
				printf("Invalid COMP Size");
			}
		}
		//case parse::COMPEQ:  output = "COMP=="; break;
		//Comp duration Assignment
		if (Graph.data_v[i].operation_name == "COMPEQ") {
			if (Graph.data_v[i].width == 1) {
				Graph.data_v[i].duration = 3.031;
			}
			else if (Graph.data_v[i].width == 2) {
				Graph.data_v[i].duration = 3.934;
			}
			else if (Graph.data_v[i].width == 8) {
				Graph.data_v[i].duration = 5.949;
			}
			else if (Graph.data_v[i].width == 16) {
				Graph.data_v[i].duration = 6.256;
			}
			else if (Graph.data_v[i].width == 32) {
				Graph.data_v[i].duration = 7.264;
			}
			else if (Graph.data_v[i].width == 64) {
				Graph.data_v[i].duration = 8.416;
			}
			else {
				printf("Invalid COMP Size");
			}
		}
		//case parse::COMPGT:  output = "COMP>"; break;
		//Comp duration Assignment
		if (Graph.data_v[i].operation_name == "COMPGT") {
			if (Graph.data_v[i].width == 1) {
				Graph.data_v[i].duration = 3.031;
			}
			else if (Graph.data_v[i].width == 2) {
				Graph.data_v[i].duration = 3.934;
			}
			else if (Graph.data_v[i].width == 8) {
				Graph.data_v[i].duration = 5.949;
			}
			else if (Graph.data_v[i].width == 16) {
				Graph.data_v[i].duration = 6.256;
			}
			else if (Graph.data_v[i].width == 32) {
				Graph.data_v[i].duration = 7.264;
			}
			else if (Graph.data_v[i].width == 64) {
				Graph.data_v[i].duration = 8.416;
			}
			else {
				printf("Invalid COMP Size");
			}
		}
		//case parse::MUX2X1:  output = "MUX2X1"; break;
		//Mux duration Assignment
		if (Graph.data_v[i].operation_name == "MUX2X1") {
			if (Graph.data_v[i].width == 1) {
				Graph.data_v[i].duration = 4.083;
			}
			else if (Graph.data_v[i].width == 2) {
				Graph.data_v[i].duration = 4.115;
			}
			else if (Graph.data_v[i].width == 8) {
				Graph.data_v[i].duration = 4.815;
			}
			else if (Graph.data_v[i].width == 16) {
				Graph.data_v[i].duration = 5.623;
			}
			else if (Graph.data_v[i].width == 32) {
				Graph.data_v[i].duration = 8.079;
			}
			else if (Graph.data_v[i].width == 64) {
				Graph.data_v[i].duration = 8.766;
			}
			else {
				printf("Invalid MUX Size");
			}
		}
		//case parse::SHR:     output = "SHR"; break;
		//Shr duration Assignment
		if (Graph.data_v[i].operation_name == "SHR") {
			if (Graph.data_v[i].width == 1) {
				Graph.data_v[i].duration = 3.644;
			}
			else if (Graph.data_v[i].width == 2) {
				Graph.data_v[i].duration = 4.007;
			}
			else if (Graph.data_v[i].width == 8) {
				Graph.data_v[i].duration = 5.178;
			}
			else if (Graph.data_v[i].width == 16) {
				Graph.data_v[i].duration = 6.460;
			}
			else if (Graph.data_v[i].width == 32) {
				Graph.data_v[i].duration = 8.819;
			}
			else if (Graph.data_v[i].width == 64) {
				Graph.data_v[i].duration = 11.095;
			}
			else {
				printf("Invalid SHR Size");
			}
		}
		//case parse::SHL:     output = "SHL"; break;
		//Shl duration Assignment
		if (Graph.data_v[i].operation_name == "SHL") {
			if (Graph.data_v[i].width == 1) {
				Graph.data_v[i].duration = 3.614;
			}
			else if (Graph.data_v[i].width == 2) {
				Graph.data_v[i].duration = 3.980;
			}
			else if (Graph.data_v[i].width == 8) {
				Graph.data_v[i].duration = 5.152;
			}
			else if (Graph.data_v[i].width == 16) {
				Graph.data_v[i].duration = 6.549;
			}
			else if (Graph.data_v[i].width == 32) {
				Graph.data_v[i].duration = 8.565;
			}
			else if (Graph.data_v[i].width == 64) {
				Graph.data_v[i].duration = 11.220;
			}
			else {
				printf("Invalid SHL Size");
			}
		}
		//case parse::DIV:     output = "DIV"; break;
		//Div duration Assignment
		if (Graph.data_v[i].operation_name == "DIV") {
			if (Graph.data_v[i].width == 1) {
				Graph.data_v[i].duration = 0.619;
			}
			else if (Graph.data_v[i].width == 2) {
				Graph.data_v[i].duration = 2.144;
			}
			else if (Graph.data_v[i].width == 8) {
				Graph.data_v[i].duration = 15.439;
			}
			else if (Graph.data_v[i].width == 16) {
				Graph.data_v[i].duration = 33.093;
			}
			else if (Graph.data_v[i].width == 32) {
				Graph.data_v[i].duration = 86.312;
			}
			else if (Graph.data_v[i].width == 64) {
				Graph.data_v[i].duration = 243.233;
			}
			else {
				printf("Invalid SHL Size");
			}
		}
		//case parse::MOD:     output = "MOD"; break;
		//Mod duration Assignment
		if (Graph.data_v[i].operation_name == "MOD") {
			if (Graph.data_v[i].width == 1) {
				Graph.data_v[i].duration = 0.758;
			}
			else if (Graph.data_v[i].width == 2) {
				Graph.data_v[i].duration = 2.149;
			}
			else if (Graph.data_v[i].width == 8) {
				Graph.data_v[i].duration = 16.078;
			}
			else if (Graph.data_v[i].width == 16) {
				Graph.data_v[i].duration = 35.563;
			}
			else if (Graph.data_v[i].width == 32) {
				Graph.data_v[i].duration = 88.142;
			}
			else if (Graph.data_v[i].width == 64) {
				Graph.data_v[i].duration = 250.583;
			}
			else {
				printf("Invalid MOD Size");
			}
		}
		//case parse::INC:     output = "INC"; break;
		//Inc duration Assignment
		if (Graph.data_v[i].operation_name == "INC") {
			if (Graph.data_v[i].width == 1) {
				Graph.data_v[i].duration = 1.792;
			}
			else if (Graph.data_v[i].width == 2) {
				Graph.data_v[i].duration = 2.218;
			}
			else if (Graph.data_v[i].width == 8) {
				Graph.data_v[i].duration = 3.111;
			}
			else if (Graph.data_v[i].width == 16) {
				Graph.data_v[i].duration = 3.471;
			}
			else if (Graph.data_v[i].width == 32) {
				Graph.data_v[i].duration = 4.347;
			}
			else if (Graph.data_v[i].width == 64) {
				Graph.data_v[i].duration = 6.200;
			}
			else {
				printf("Invalid INC Size");
			}
		}
		//case parse::DEC:     output = "DEC"; break;
		//Dec duration Assignment
		if (Graph.data_v[i].operation_name == "DEC") {
			if (Graph.data_v[i].width == 1) {
				Graph.data_v[i].duration = 1.792;
			}
			else if (Graph.data_v[i].width == 2) {
				Graph.data_v[i].duration = 2.218;
			}
			else if (Graph.data_v[i].width == 8) {
				Graph.data_v[i].duration = 3.108;
			}
			else if (Graph.data_v[i].width == 16) {
				Graph.data_v[i].duration = 3.701;
			}
			else if (Graph.data_v[i].width == 32) {
				Graph.data_v[i].duration = 4.685;
			}
			else if (Graph.data_v[i].width == 64) {
				Graph.data_v[i].duration = 6.503;
			}
			else {
				printf("Invalid DEC Size");
			}
		}
		//case parse::WIRE:    output = "WIRE"; break;
		//wire duration Assignment
		if (Graph.data_v[i].operation_name == "WIRE") {
			Graph.data_v[i].duration = 0;
		}
	}
}
