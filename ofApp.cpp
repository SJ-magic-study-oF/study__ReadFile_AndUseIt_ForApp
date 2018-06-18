/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

/******************************
******************************/
void ofApp::exit()
{
	fclose(fp_out);
}

//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	********************/
	ofSetBackgroundAuto(true);
	
	ofSetWindowTitle("study:ofBuffer");
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	// ofEnableBlendMode(OF_BLENDMODE_ADD);
	// ofEnableSmoothing();
	
	/********************
	********************/
	fp_in	= fopen("../../../data/sample_motion_data.csv", "r");
	fp_out	= fopen("../../../data/Log.csv", "w");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
		case ' ':
			OutToFile();
			printf("output 1 line\n");
			break;
	}
}

/******************************
******************************/
bool ofApp::checkIf_ContentsExist(char* ret, char* buf)
{
	if( (ret == NULL) || (buf == NULL)) return false;
	
	string str_Line = buf;
	Align(str_Line);
	vector<string> str_vals = ofSplitString(str_Line, ",");
	if( (str_vals.size() == 0) || (str_vals[0] == "") ){ // no_data or exist text but it's",,,,,,,".
		return false;
	}else{
		return true;
	}
}

/******************************
******************************/
void ofApp::OutToFile()
{
	char* ret;
	char buf[MAX_BUFSIZE];
	
	ret = fgets(buf, MAX_BUFSIZE, fp_in);
	if(!checkIf_ContentsExist(ret, buf)){
		fseek(fp_in, 0, SEEK_SET);
		printf("fp_in to Top\n");
		
		ret = fgets(buf, MAX_BUFSIZE, fp_in);
		if(!checkIf_ContentsExist(ret, buf)){
			printf("No Contents in fp_in\n");
			std::exit(1);
		}
	}
	
	string str_Line = buf;
	// YennToCR(str_Line); // no need this time(from experiment).
	Align(str_Line);
	
	vector<string> str_vals = ofSplitString(str_Line, ",");
	for(int i=0; i < str_vals.size(); i++){
		fprintf(fp_out, "%s,", str_vals[i].c_str());
	}
	fprintf(fp_out, "\n");
}

/******************************
******************************/
void ofApp::Align(string& s)
{
	/********************
	delete : space, tab 
	********************/
	size_t pos;
	while((pos = s.find_first_of(" 　\t\n\r")) != string::npos){ // 半角・全角space, \t 改行 削除
		s.erase(pos, 1);
	}
}

/******************************
今回未使用だが、実際にCodeを読み込んで見て、必要なら使用すること.
参考までに残しておく.


description
	外部fileから文字列を読み込んだ時、
	string文字列中の"\n"は実は"\\n"(\\ + n の２文字)、改行文字のリテラルではない.
	本methodは、これを変換するためのmethod.
	
参考
	http://d.hatena.ne.jp/p95095yy/20050222/1109119001
	注意)
		本URLでは、find_first_of を使っているが、間違い.
		find_first_of()は、「列挙された1文字ずつを」探しに行く.
		正解は、「文字列」を探しに行く find().

その他、stringの便利なmethod
	find_first_of, find_last_of, find_first_not_of, find_first_last_of
******************************/
void ofApp::YennToCR(string& s)
{
	string YenN = "\\n";
	string CR   = "\n";
	
	// size_t pos = s.find_first_of(YenN, 0); // NG. don't use find_first_of here.
	size_t pos = s.find(YenN, 0);

	while(pos != string::npos){
		s.replace(pos, YenN.length(), CR);
		pos = s.find(YenN, pos);
	}
}

/******************************
今回未使用だが、実際にCodeを読み込んで見て、必要なら使用すること.
参考までに残しておく.


description
	外部fileに戻す時は、
	"\n" -> "\\n"
******************************/
string ofApp::CR_To_Yenn(string s)
{
	string YenN = "\\n";
	string CR   = "\n";
	
	size_t pos = s.find(CR, 0);

	while(pos != string::npos){
		s.replace(pos, CR.length(), YenN);
		pos = s.find(CR, pos);
	}
	
	return s;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
