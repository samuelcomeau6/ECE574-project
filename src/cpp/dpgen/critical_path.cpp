#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include "path.h"
#include "data_list.h"
#include "data_type.h"
#include "critical_path.h"

using namespace std;

void TopSort(data_list * Graph, data_list * List, data_type vertex) {

	for (int i = 0; i<Graph->data_v.size(); i++) {

		Graph->data_v[i].color = "White";
		TopSortVisit(Graph, List, Graph->data_v[i]);

	}
}

void TopSortVisit(data_list * Graph, data_list * List, data_type uVertex) {


	uVertex.color = "Gray";
	for (int i = 0; i<Graph->data_v.size(); i++) {
		if (Graph->data_v[i].is_operation || Graph->data_v[i].is_mux) {
			if (!uVertex.is_operation && !uVertex.is_output && !uVertex.is_mux) {
				if ((strcmp(uVertex.input_1_name, Graph->data_v[i].input_1_name) == 0 ||
					strcmp(uVertex.input_1_name, Graph->data_v[i].input_2_name) == 0)) {
					if (Graph->data_v[i].color == "White") {
						if ((strcmp(Graph->data_v[i].operation_name, "REG") != 0)) {
						    //Not a register
							List->data_v.push_back(Graph->data_v[i]);
							#ifdef DEBUG
							    printf("Added #%d:%s\n", i, Graph->data_v[i].operation_name);
							#endif
							TopSortVisit(Graph, List, Graph->data_v[i]);
						}
					}
					Graph->data_v[i].color = "Black";
				}
			}
			else if (!uVertex.is_output) {
				if (strcmp(uVertex.output_name, Graph->data_v[i].input_1_name) == 0 ||
					strcmp(uVertex.output_name, Graph->data_v[i].input_2_name) == 0 ||
					strcmp(uVertex.output_name, Graph->data_v[i].shift_select) == 0) {
					if (Graph->data_v[i].color == "White") {
						if (strcmp(Graph->data_v[i].operation_name, "REG") != 0) {
							List->data_v.push_back(Graph->data_v[i]);
							#ifdef DEBUG
							printf("Added #%d:%s\n", i, Graph->data_v[i].operation_name);
							#endif
							Graph->data_v[i].color = "Black";
							TopSortVisit(Graph, List, Graph->data_v[i]);
						}
					}
					Graph->data_v[i].color = "Black";
				}
			}
			else {
				continue;
			}

		}
		else if (Graph->data_v[i].is_assignment && Graph->data_v[i].color == "White") {
		    //Is a register
			Graph->data_v[i].color = "Black";
			List->data_v.push_back(Graph->data_v[i]);
			#ifdef DEBUG
			    printf("Added #%d:%s\n", i, Graph->data_v[i].operation_name);
			#endif
			return;
		}
        else{
			continue;
		}
	}
}

bool nodeCompare(data_type graphNode, data_type listNode) {
	bool output = 1;
	if (graphNode.input_1_name != NULL && listNode.input_1_name != NULL)
	{
		output = output && !strcmp(graphNode.input_1_name, listNode.input_1_name);
	}
	else { return (graphNode.input_1_name == listNode.input_1_name); }
	if (graphNode.input_2_name != NULL &&  listNode.input_2_name != NULL) {
		output = output && !strcmp(graphNode.input_2_name, listNode.input_2_name);
	}
	else { return(graphNode.input_2_name == listNode.input_2_name); }
	if (graphNode.output_name != NULL && listNode.output_name != NULL) {
		output = output && !strcmp(graphNode.output_name, listNode.output_name);
	}
	else { return(graphNode.output_name == listNode.output_name); }
	if (graphNode.operation_name != NULL && listNode.operation_name != NULL) {
		output = output && !strcmp(graphNode.operation_name, listNode.operation_name);
	}
	else { return(graphNode.operation_name == listNode.operation_name); }
	output = output && (graphNode.is_input == listNode.is_input);
	output = output && (graphNode.is_output == listNode.is_output);
	output = output && (graphNode.is_operation == listNode.is_operation);
	output = output && (graphNode.is_mux == listNode.is_mux);
	output = output && (graphNode.is_wire == listNode.is_wire);
	output = output && (graphNode.is_reg == listNode.is_reg);
	output = output && (graphNode.is_signed == listNode.is_signed);
	output = output && (graphNode.is_assignment == listNode.is_assignment);
	output = output && (graphNode.width == listNode.width);
	output = output && (graphNode.duration == listNode.duration);
	output = output && (graphNode.color == listNode.color);
	return output;

}

float LongestPath(data_list * Graph) {

	int max = 0;
	float pathDur = 0;
	float critPathDur = 0;
	vector<float> pathDurStor;
	vector<string> nodeCollect;
	bool eqNodes = 0;

	for (int i = 0; i<Graph->data_v.size(); i++) {
		data_list List;
		if (Graph->data_v[i].is_operation || Graph->data_v[i].is_mux == 1) {
			TopSort(Graph, &List, Graph->data_v[i]);
			for (int i = 0; i<List.data_v.size(); i++) {

				eqNodes = nodeCompare(Graph->data_v[i], List.data_v[i]);

				if ((strcmp(List.data_v[i].operation_name, "REG") == 0 && (eqNodes == 1)) || strcmp(List.data_v[i].operation_name, "REG") != 0) {
					pathDur = List.data_v[i].duration + pathDur;
					//Node tracker vector
					nodeCollect.push_back(List.data_v[i].operation_name);
					Graph->data_v[i].color = "Black";
					#ifdef DEBUG
					printf("Path duration after i:%d:%s:%f is %fns\n", i, List.data_v[i].operation_name, List.data_v[i].duration, pathDur);
					#endif
				}
			}
			pathDurStor.push_back(pathDur);
			pathDur = 0;
		}
		else {
			continue;
		}
	}

	critPathDur = *max_element(pathDurStor.begin(), pathDurStor.end());

	return critPathDur;

}



void assignDuration(data_list * Graph) {

	for (int i = 0; i < Graph->data_v.size(); i++) {
		if (Graph->data_v[i].operation_name == NULL) {
			fprintf(stderr, "Malformed operator:");
			fprintf(stderr, " input1:%s input2:%s output:%s",
				Graph->data_v[i].input_1_name, Graph->data_v[i].input_2_name, Graph->data_v[i].output_name);
		}
		//Register duration Assignment
		if (strcmp(Graph->data_v[i].operation_name, "REG") == 0) {
			if (Graph->data_v[i].width == 1) {
				Graph->data_v[i].duration = 2.616;
			}
			else if (Graph->data_v[i].width == 2) {
				Graph->data_v[i].duration = 2.644;
			}
			else if (Graph->data_v[i].width == 8) {
				Graph->data_v[i].duration = 2.879;
			}
			else if (Graph->data_v[i].width == 16) {
				Graph->data_v[i].duration = 3.061;
			}
			else if (Graph->data_v[i].width == 32) {
				Graph->data_v[i].duration = 3.602;
			}
			else if (Graph->data_v[i].width == 64) {
				Graph->data_v[i].duration = 3.966;
			}
			else {
				fprintf(stderr, "Invalid REG Size:%d\n", Graph->data_v[i].width);
			}
		}
		//case parse::ADD:     output = "ADD"; break;

		//Add duration Assignment
		if (strcmp(Graph->data_v[i].operation_name, "ADD") == 0) {
			if (Graph->data_v[i].width == 1) {
				Graph->data_v[i].duration = 2.704;
			}
			else if (Graph->data_v[i].width == 2) {
				Graph->data_v[i].duration = 3.713;
			}
			else if (Graph->data_v[i].width == 8) {
				Graph->data_v[i].duration = 4.924;
			}
			else if (Graph->data_v[i].width == 16) {
				Graph->data_v[i].duration = 5.638;
			}
			else if (Graph->data_v[i].width == 32) {
				Graph->data_v[i].duration = 7.270;
			}
			else if (Graph->data_v[i].width == 64) {
				Graph->data_v[i].duration = 9.566;
			}
			else {
				fprintf(stderr, "Invalid ADD Size:%d\n", Graph->data_v[i].width);
			}
		}
		//case parse::SUB:     output = "SUB"; break;
		//Subtractor duration Assignment
		if (strcmp(Graph->data_v[i].operation_name, "SUB") == 0) {
			if (Graph->data_v[i].width == 1) {
				Graph->data_v[i].duration = 3.024;
			}
			else if (Graph->data_v[i].width == 2) {
				Graph->data_v[i].duration = 3.412;
			}
			else if (Graph->data_v[i].width == 8) {
				Graph->data_v[i].duration = 4.890;
			}
			else if (Graph->data_v[i].width == 16) {
				Graph->data_v[i].duration = 5.569;
			}
			else if (Graph->data_v[i].width == 32) {
				Graph->data_v[i].duration = 7.253;
			}
			else if (Graph->data_v[i].width == 64) {
				Graph->data_v[i].duration = 9.566;
			}
			else {
				fprintf(stderr, "Invalid SUB Size:%d\n", Graph->data_v[i].width);
			}
		}
		//case parse::MUL:     output = "MUL"; break;
		//Mul duration Assignment
		if (strcmp(Graph->data_v[i].operation_name, "MUL") == 0) {
			if (Graph->data_v[i].width == 1) {
				Graph->data_v[i].duration = 2.438;
			}
			else if (Graph->data_v[i].width == 2) {
				Graph->data_v[i].duration = 3.651;
			}
			else if (Graph->data_v[i].width == 8) {
				Graph->data_v[i].duration = 7.453;
			}
			else if (Graph->data_v[i].width == 16) {
				Graph->data_v[i].duration = 7.811;
			}
			else if (Graph->data_v[i].width == 32) {
				Graph->data_v[i].duration = 12.395;
			}
			else if (Graph->data_v[i].width == 64) {
				Graph->data_v[i].duration = 15.354;
			}
			else {
				fprintf(stderr, "Invalid MUL Size:%d\n", Graph->data_v[i].width);
			}
		}
		//case parse::COMPLT:  output = "COMP<"; break;
		//COMP duration Assignment
		if (strcmp(Graph->data_v[i].operation_name, "COMP<") == 0) {
			if (Graph->data_v[i].width == 1) {
				Graph->data_v[i].duration = 3.031;
			}
			else if (Graph->data_v[i].width == 2) {
				Graph->data_v[i].duration = 3.934;
			}
			else if (Graph->data_v[i].width == 8) {
				Graph->data_v[i].duration = 5.949;
			}
			else if (Graph->data_v[i].width == 16) {
				Graph->data_v[i].duration = 6.256;
			}
			else if (Graph->data_v[i].width == 32) {
				Graph->data_v[i].duration = 7.264;
			}
			else if (Graph->data_v[i].width == 64) {
				Graph->data_v[i].duration = 8.416;
			}
			else {
				fprintf(stderr, "Invalid COMP Size:%d\n", Graph->data_v[i].width);
			}
		}
		//case parse::COMPEQ:  output = "COMP=="; break;
		//Comp duration Assignment
		if (strcmp(Graph->data_v[i].operation_name, "COMP==") == 0) {
			if (Graph->data_v[i].width == 1) {
				Graph->data_v[i].duration = 3.031;
			}
			else if (Graph->data_v[i].width == 2) {
				Graph->data_v[i].duration = 3.934;
			}
			else if (Graph->data_v[i].width == 8) {
				Graph->data_v[i].duration = 5.949;
			}
			else if (Graph->data_v[i].width == 16) {
				Graph->data_v[i].duration = 6.256;
			}
			else if (Graph->data_v[i].width == 32) {
				Graph->data_v[i].duration = 7.264;
			}
			else if (Graph->data_v[i].width == 64) {
				Graph->data_v[i].duration = 8.416;
			}
			else {
				fprintf(stderr, "Invalid COMP Size:%d\n", Graph->data_v[i].width);
			}
		}
		//case parse::COMPGT:  output = "COMP>"; break;
		//Comp duration Assignment
		if (strcmp(Graph->data_v[i].operation_name, "COMP>") == 0) {
			if (Graph->data_v[i].width == 1) {
				Graph->data_v[i].duration = 3.031;
			}
			else if (Graph->data_v[i].width == 2) {
				Graph->data_v[i].duration = 3.934;
			}
			else if (Graph->data_v[i].width == 8) {
				Graph->data_v[i].duration = 5.949;
			}
			else if (Graph->data_v[i].width == 16) {
				Graph->data_v[i].duration = 6.256;
			}
			else if (Graph->data_v[i].width == 32) {
				Graph->data_v[i].duration = 7.264;
			}
			else if (Graph->data_v[i].width == 64) {
				Graph->data_v[i].duration = 8.416;
			}
			else {
				fprintf(stderr, "Invalid COMP Size:%d\n", Graph->data_v[i].width);
			}
		}
		//case parse::MUX2X1:  output = "MUX2X1"; break;
		//Mux duration Assignment
		if (Graph->data_v[i].is_mux) {
			if (Graph->data_v[i].width == 1) {
				Graph->data_v[i].duration = 4.083;
			}
			else if (Graph->data_v[i].width == 2) {
				Graph->data_v[i].duration = 4.115;
			}
			else if (Graph->data_v[i].width == 8) {
				Graph->data_v[i].duration = 4.815;
			}
			else if (Graph->data_v[i].width == 16) {
				Graph->data_v[i].duration = 5.623;
			}
			else if (Graph->data_v[i].width == 32) {
				Graph->data_v[i].duration = 8.079;
			}
			else if (Graph->data_v[i].width == 64) {
				Graph->data_v[i].duration = 8.766;
			}
			else {
				fprintf(stderr, "Invalid MUX Size:%d\n", Graph->data_v[i].width);
			}
		}
		//case parse::SHR:     output = "SHR"; break;
		//Shr duration Assignment
		if (strcmp(Graph->data_v[i].operation_name, "SHR") == 0) {
			if (Graph->data_v[i].width == 1) {
				Graph->data_v[i].duration = 3.644;
			}
			else if (Graph->data_v[i].width == 2) {
				Graph->data_v[i].duration = 4.007;
			}
			else if (Graph->data_v[i].width == 8) {
				Graph->data_v[i].duration = 5.178;
			}
			else if (Graph->data_v[i].width == 16) {
				Graph->data_v[i].duration = 6.460;
			}
			else if (Graph->data_v[i].width == 32) {
				Graph->data_v[i].duration = 8.819;
			}
			else if (Graph->data_v[i].width == 64) {
				Graph->data_v[i].duration = 11.095;
			}
			else {
				fprintf(stderr, "Invalid SHR Size:%d\n", Graph->data_v[i].width);
			}
		}
		//case parse::SHL:     output = "SHL"; break;
		//Shl duration Assignment
		if (strcmp(Graph->data_v[i].operation_name, "SHL") == 0) {
			if (Graph->data_v[i].width == 1) {
				Graph->data_v[i].duration = 3.614;
			}
			else if (Graph->data_v[i].width == 2) {
				Graph->data_v[i].duration = 3.980;
			}
			else if (Graph->data_v[i].width == 8) {
				Graph->data_v[i].duration = 5.152;
			}
			else if (Graph->data_v[i].width == 16) {
				Graph->data_v[i].duration = 6.549;
			}
			else if (Graph->data_v[i].width == 32) {
				Graph->data_v[i].duration = 8.565;
			}
			else if (Graph->data_v[i].width == 64) {
				Graph->data_v[i].duration = 11.220;
			}
			else {
				fprintf(stderr, "Invalid SHL Size:%d\n", Graph->data_v[i].width);
			}
		}
		//case parse::DIV:     output = "DIV"; break;
		//Div duration Assignment
		if (strcmp(Graph->data_v[i].operation_name, "DIV") == 0) {
			if (Graph->data_v[i].width == 1) {
				Graph->data_v[i].duration = 0.619;
			}
			else if (Graph->data_v[i].width == 2) {
				Graph->data_v[i].duration = 2.144;
			}
			else if (Graph->data_v[i].width == 8) {
				Graph->data_v[i].duration = 15.439;
			}
			else if (Graph->data_v[i].width == 16) {
				Graph->data_v[i].duration = 33.093;
			}
			else if (Graph->data_v[i].width == 32) {
				Graph->data_v[i].duration = 86.312;
			}
			else if (Graph->data_v[i].width == 64) {
				Graph->data_v[i].duration = 243.233;
			}
			else {
				fprintf(stderr, "Invalid SHL Size:%d\n", Graph->data_v[i].width);
			}
		}
		//case parse::MOD:     output = "MOD"; break;
		//Mod duration Assignment
		if (strcmp(Graph->data_v[i].operation_name, "MOD") == 0) {
			if (Graph->data_v[i].width == 1) {
				Graph->data_v[i].duration = 0.758;
			}
			else if (Graph->data_v[i].width == 2) {
				Graph->data_v[i].duration = 2.149;
			}
			else if (Graph->data_v[i].width == 8) {
				Graph->data_v[i].duration = 16.078;
			}
			else if (Graph->data_v[i].width == 16) {
				Graph->data_v[i].duration = 35.563;
			}
			else if (Graph->data_v[i].width == 32) {
				Graph->data_v[i].duration = 88.142;
			}
			else if (Graph->data_v[i].width == 64) {
				Graph->data_v[i].duration = 250.583;
			}
			else {
				fprintf(stderr, "Invalid MOD Size:%d\n", Graph->data_v[i].width);
			}
		}
		//case parse::INC:     output = "INC"; break;
		//Inc duration Assignment
		if (strcmp(Graph->data_v[i].operation_name, "INC") == 0) {
			if (Graph->data_v[i].width == 1) {
				Graph->data_v[i].duration = 1.792;
			}
			else if (Graph->data_v[i].width == 2) {
				Graph->data_v[i].duration = 2.218;
			}
			else if (Graph->data_v[i].width == 8) {
				Graph->data_v[i].duration = 3.111;
			}
			else if (Graph->data_v[i].width == 16) {
				Graph->data_v[i].duration = 3.471;
			}
			else if (Graph->data_v[i].width == 32) {
				Graph->data_v[i].duration = 4.347;
			}
			else if (Graph->data_v[i].width == 64) {
				Graph->data_v[i].duration = 6.200;
			}
			else {
				fprintf(stderr, "Invalid INC Size:%d\n", Graph->data_v[i].width);
			}
		}
		//case parse::DEC:     output = "DEC"; break;
		//Dec duration Assignment
		if (strcmp(Graph->data_v[i].operation_name, "DEC") == 0) {
			if (Graph->data_v[i].width == 1) {
				Graph->data_v[i].duration = 1.792;
			}
			else if (Graph->data_v[i].width == 2) {
				Graph->data_v[i].duration = 2.218;
			}
			else if (Graph->data_v[i].width == 8) {
				Graph->data_v[i].duration = 3.108;
			}
			else if (Graph->data_v[i].width == 16) {
				Graph->data_v[i].duration = 3.701;
			}
			else if (Graph->data_v[i].width == 32) {
				Graph->data_v[i].duration = 4.685;
			}
			else if (Graph->data_v[i].width == 64) {
				Graph->data_v[i].duration = 6.503;
			}
			else {
				fprintf(stderr, "Invalid DEC Size:%d\n", Graph->data_v[i].width);
			}
		}
		//case parse::WIRE:    output = "WIRE"; break;
		//wire duration Assignment
		if (strcmp(Graph->data_v[i].operation_name, "WIRE") == 0) {
			Graph->data_v[i].duration = 0;
		}
#ifdef DEBUG
		printf("Assigned duration of %f ns to %d:%d'%s\n"
			, Graph->data_v[i].duration, i, Graph->data_v[i].width, Graph->data_v[i].operation_name);
#endif
	}
}
