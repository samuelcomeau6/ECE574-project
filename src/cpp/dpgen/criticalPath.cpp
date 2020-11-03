#include <iostream>
#include "path.h"
#include "data_list.h"
namespace topSort {

	for (int i = 0; i < data_list.size(); i++) {
		data_list(i).color = "white";
	}


}


namespace assignDuration {

	for (int i = 0; i < data_list.size(); i++) {

		//Register duration Assignment
		if (data_list(i).operation_name == 'REG') {
			if (data_list(i).size == 1) {
				data_list(i).duration = 2.616;
			}
			else if (data_list(i).size == 2) {
				data_list(i).duration = 2.644;
			}
			else if (data_list(i).size == 8) {
				data_list(i).duration = 2.879;
			}
			else if (data_list(i).size == 16) {
				data_list(i).duration = 3.061;
			}
			else if (data_list(i).size == 32) {
				data_list(i).duration = 3.602;
			}
			else if (data_list(i).size == 64) {
				data_list(i).duration = 3.966;
			}
			else {
				printf("Invalid REG Size");
			}
		}
		//case parse::ADD:     output = "ADD"; break;

		//Add duration Assignment
		if (data_list(i).operation_name == 'ADD') {
			if (data_list(i).size == 1) {
				data_list(i).duration = 2.704;
			}
			else if (data_list(i).size == 2) {
				data_list(i).duration = 3.713;
			}
			else if (data_list(i).size == 8) {
				data_list(i).duration = 4.924;
			}
			else if (data_list(i).size == 16) {
				data_list(i).duration = 5.638;
			}
			else if (data_list(i).size == 32) {
				data_list(i).duration = 7.270;
			}
			else if (data_list(i).size == 64) {
				data_list(i).duration = 9.566;
			}
			else {
				printf("Invalid ADD Size");
			}
		}
		//case parse::SUB:     output = "SUB"; break;
		//Subtractor duration Assignment
		if (data_list(i).operation_name == 'SUB') {
			if (data_list(i).size == 1) {
				data_list(i).duration = 3.024;
			}
			else if (data_list(i).size == 2) {
				data_list(i).duration = 3.412;
			}
			else if (data_list(i).size == 8) {
				data_list(i).duration = 4.890;
			}
			else if (data_list(i).size == 16) {
				data_list(i).duration = 5.569;
			}
			else if (data_list(i).size == 32) {
				data_list(i).duration = 7.253;
			}
			else if (data_list(i).size == 64) {
				data_list(i).duration = 9.566;
			}
			else {
				printf("Invalid SUB Size");
			}
		}
		//case parse::MUL:     output = "MUL"; break;
		//Mul duration Assignment
		if (data_list(i).operation_name == 'MUL') {
			if (data_list(i).size == 1) {
				data_list(i).duration = 2.438;
			}
			else if (data_list(i).size == 2) {
				data_list(i).duration = 3.651;
			}
			else if (data_list(i).size == 8) {
				data_list(i).duration = 7.453;
			}
			else if (data_list(i).size == 16) {
				data_list(i).duration = 7.811;
			}
			else if (data_list(i).size == 32) {
				data_list(i).duration = 12.395;
			}
			else if (data_list(i).size == 64) {
				data_list(i).duration = 15.354;
			}
			else {
				printf("Invalid MUL Size");
			}
		}
		//case parse::COMPLT:  output = "COMP<"; break;
		//COMP duration Assignment
		if (data_list(i).operation_name == 'COMPLT') {
			if (data_list(i).size == 1) {
				data_list(i).duration = 3.031;
			}
			else if (data_list(i).size == 2) {
				data_list(i).duration = 3.934;
			}
			else if (data_list(i).size == 8) {
				data_list(i).duration = 5.949;
			}
			else if (data_list(i).size == 16) {
				data_list(i).duration = 6.256;
			}
			else if (data_list(i).size == 32) {
				data_list(i).duration = 7.264;
			}
			else if (data_list(i).size == 64) {
				data_list(i).duration = 8.416;
			}
			else {
				printf("Invalid COMP Size");
			}
		}
		//case parse::COMPEQ:  output = "COMP=="; break;
		//Comp duration Assignment
		if (data_list(i).operation_name == 'COMPEQ') {
			if (data_list(i).size == 1) {
				data_list(i).duration = 3.031;
			}
			else if (data_list(i).size == 2) {
				data_list(i).duration = 3.934;
			}
			else if (data_list(i).size == 8) {
				data_list(i).duration = 5.949;
			}
			else if (data_list(i).size == 16) {
				data_list(i).duration = 6.256;
			}
			else if (data_list(i).size == 32) {
				data_list(i).duration = 7.264;
			}
			else if (data_list(i).size == 64) {
				data_list(i).duration = 8.416;
			}
			else {
				printf("Invalid COMP Size");
			}
		}
		//case parse::COMPGT:  output = "COMP>"; break;
		//Comp duration Assignment
		if (data_list(i).operation_name == 'COMPGT') {
			if (data_list(i).size == 1) {
				data_list(i).duration = 3.031;
			}
			else if (data_list(i).size == 2) {
				data_list(i).duration = 3.934;
			}
			else if (data_list(i).size == 8) {
				data_list(i).duration = 5.949;
			}
			else if (data_list(i).size == 16) {
				data_list(i).duration = 6.256;
			}
			else if (data_list(i).size == 32) {
				data_list(i).duration = 7.264;
			}
			else if (data_list(i).size == 64) {
				data_list(i).duration = 8.416;
			}
			else {
				printf("Invalid COMP Size");
			}
		}
		//case parse::COMPLTE: output = "COMP<="; break;
		//Comp duration Assignment
		if (data_list(i).operation_name == 'COMPLTE') {
			if (data_list(i).size == 1) {
				data_list(i).duration = 3.031;
			}
			else if (data_list(i).size == 2) {
				data_list(i).duration = 3.934;
			}
			else if (data_list(i).size == 8) {
				data_list(i).duration = 5.949;
			}
			else if (data_list(i).size == 16) {
				data_list(i).duration = 6.256;
			}
			else if (data_list(i).size == 32) {
				data_list(i).duration = 7.264;
			}
			else if (data_list(i).size == 64) {
				data_list(i).duration = 8.416;
			}
			else {
				printf("Invalid COMP Size");
			}
		}
		//case parse::COMPGTE: output = "COMP>="; break;
		//Comp duration Assignment
		if (data_list(i).operation_name == 'COMPGTE') {
			if (data_list(i).size == 1) {
				data_list(i).duration = 3.031;
			}
			else if (data_list(i).size == 2) {
				data_list(i).duration = 3.934;
			}
			else if (data_list(i).size == 8) {
				data_list(i).duration = 5.949;
			}
			else if (data_list(i).size == 16) {
				data_list(i).duration = 6.256;
			}
			else if (data_list(i).size == 32) {
				data_list(i).duration = 7.264;
			}
			else if (data_list(i).size == 64) {
				data_list(i).duration = 8.416;
			}
			else {
				printf("Invalid COMP Size");
			}
		}
		//case parse::MUX2X1:  output = "MUX2X1"; break;
		//Mux duration Assignment
		if (data_list(i).operation_name == 'MUX2X1') {
			if (data_list(i).size == 1) {
				data_list(i).duration = 4.083;
			}
			else if (data_list(i).size == 2) {
				data_list(i).duration = 4.115;
			}
			else if (data_list(i).size == 8) {
				data_list(i).duration = 4.815;
			}
			else if (data_list(i).size == 16) {
				data_list(i).duration = 5.623;
			}
			else if (data_list(i).size == 32) {
				data_list(i).duration = 8.079;
			}
			else if (data_list(i).size == 64) {
				data_list(i).duration = 8.766;
			}
			else {
				printf("Invalid MUX Size");
			}
		}
		//case parse::SHR:     output = "SHR"; break;
		//Shr duration Assignment
		if (data_list(i).operation_name == 'SHR') {
			if (data_list(i).size == 1) {
				data_list(i).duration = 3.644;
			}
			else if (data_list(i).size == 2) {
				data_list(i).duration = 4.007;
			}
			else if (data_list(i).size == 8) {
				data_list(i).duration = 5.178;
			}
			else if (data_list(i).size == 16) {
				data_list(i).duration = 6.460;
			}
			else if (data_list(i).size == 32) {
				data_list(i).duration = 8.819;
			}
			else if (data_list(i).size == 64) {
				data_list(i).duration = 11.095;
			}
			else {
				printf("Invalid SHR Size");
			}
		}
		//case parse::SHL:     output = "SHL"; break;
		//Shl duration Assignment
		if (data_list(i).operation_name == 'SHL') {
			if (data_list(i).size == 1) {
				data_list(i).duration = 3.614;
			}
			else if (data_list(i).size == 2) {
				data_list(i).duration = 3.980;
			}
			else if (data_list(i).size == 8) {
				data_list(i).duration = 5.152;
			}
			else if (data_list(i).size == 16) {
				data_list(i).duration = 6.549;
			}
			else if (data_list(i).size == 32) {
				data_list(i).duration = 8.565;
			}
			else if (data_list(i).size == 64) {
				data_list(i).duration = 11.220;
			}
			else {
				printf("Invalid SHL Size");
			}
		}
		//case parse::DIV:     output = "DIV"; break;
		//Div duration Assignment
		if (data_list(i).operation_name == 'DIV') {
			if (data_list(i).size == 1) {
				data_list(i).duration = 0.619;
			}
			else if (data_list(i).size == 2) {
				data_list(i).duration = 2.144;
			}
			else if (data_list(i).size == 8) {
				data_list(i).duration = 15.439;
			}
			else if (data_list(i).size == 16) {
				data_list(i).duration = 33.093;
			}
			else if (data_list(i).size == 32) {
				data_list(i).duration = 86.312;
			}
			else if (data_list(i).size == 64) {
				data_list(i).duration = 243.233;
			}
			else {
				printf("Invalid SHL Size");
			}
		}
		//case parse::MOD:     output = "MOD"; break;
		//Mod duration Assignment
		if (data_list(i).operation_name == 'MOD') {
			if (data_list(i).size == 1) {
				data_list(i).duration = 0.758;
			}
			else if (data_list(i).size == 2) {
				data_list(i).duration = 2.149;
			}
			else if (data_list(i).size == 8) {
				data_list(i).duration = 16.078;
			}
			else if (data_list(i).size == 16) {
				data_list(i).duration = 35.563;
			}
			else if (data_list(i).size == 32) {
				data_list(i).duration = 88.142;
			}
			else if (data_list(i).size == 64) {
				data_list(i).duration = 250.583;
			}
			else {
				printf("Invalid MOD Size");
			}
		}
		//case parse::INC:     output = "INC"; break;
		//Inc duration Assignment
		if (data_list(i).operation_name == 'INC') {
			if (data_list(i).size == 1) {
				data_list(i).duration = 1.792;
			}
			else if (data_list(i).size == 2) {
				data_list(i).duration = 2.218;
			}
			else if (data_list(i).size == 8) {
				data_list(i).duration = 3.111;
			}
			else if (data_list(i).size == 16) {
				data_list(i).duration = 3.471;
			}
			else if (data_list(i).size == 32) {
				data_list(i).duration = 4.347;
			}
			else if (data_list(i).size == 64) {
				data_list(i).duration = 6.200;
			}
			else {
				printf("Invalid INC Size");
			}
		}
		//case parse::DEC:     output = "DEC"; break;
		//Dec duration Assignment
		if (data_list(i).operation_name == 'DEC') {
			if (data_list(i).size == 1) {
				data_list(i).duration = 1.792;
			}
			else if (data_list(i).size == 2) {
				data_list(i).duration = 2.218;
			}
			else if (data_list(i).size == 8) {
				data_list(i).duration = 3.108;
			}
			else if (data_list(i).size == 16) {
				data_list(i).duration = 3.701;
			}
			else if (data_list(i).size == 32) {
				data_list(i).duration = 4.685;
			}
			else if (data_list(i).size == 64) {
				data_list(i).duration = 6.503;
			}
			else {
				printf("Invalid DEC Size");
			}
		}
		//case parse::WIRE:    output = "WIRE"; break;
		//wire duration Assignment
		if (data_list(i).operation_name == 'WIRE') {
			data_list(i).duration = 0;
		}
	}
}
