#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <stdlib.h>
#include <TStyle.h>
#include <TH2D.h>
#include <TLegend.h>
#include <TColor.h>
#include <math.h>
#include <THnSparse.h>
#include <map>
#include <string>
#include <vector>
#include <random>
#include "THnSparse.h"
#include "TF1.h"
#include "TSystem.h"
#include "TLorentzVector.h"
#include "TGraphAsymmErrors.h"
#include <iomanip>
#include <sys/stat.h>
#include <time.h>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidcsv.h"
#include "onnxruntime_cxx_api.h"

using namespace std;



//-------------------------------------------------------------------------
// ONNX Model
//-------------------------------------------------------------------------
class ONNX_MODEL {
    private:
        Ort::Session session{nullptr};
        Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu( OrtAllocatorType::OrtArenaAllocator, OrtMemType::OrtMemTypeDefault);
        size_t numInputNodes;
        size_t numOutputNodes;

    public:
        void readFile( string model_file ){
            Ort::SessionOptions sessionOptions;
            sessionOptions.SetIntraOpNumThreads(1);
            sessionOptions.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);
            Ort::Env env(OrtLoggingLevel::ORT_LOGGING_LEVEL_WARNING, "onnx_model");
            Ort::Session session_tmp(env, model_file.c_str(), sessionOptions);
            session = std::move(session_tmp);
            numInputNodes = session.GetInputCount();
            numOutputNodes = session.GetOutputCount();
        }

        vector<float> predict( const char* const* inputNames, vector<vector<float>> inputTensorValues, vector<vector<int64_t>> inputTensorDims, const char* const* outputNames, vector<vector<float>> outputTensorValues, vector<vector<int64_t>> outputTensorDims ){

            vector<Ort::Value> inputTensors;
            for (size_t i = 0; i < numInputNodes; i++){
                inputTensors.push_back(Ort::Value::CreateTensor<float>( memoryInfo, inputTensorValues[i].data(), inputTensorValues[i].size(), inputTensorDims[i].data(), inputTensorDims[i].size()));
            }

            vector<Ort::Value> outputTensors;
            for (size_t i = 0; i < numOutputNodes; i++){
                outputTensors.push_back(Ort::Value::CreateTensor<float>( memoryInfo, outputTensorValues[i].data(), outputTensorValues[i].size(), outputTensorDims[i].data(), outputTensorDims[i].size()));
            }

            session.Run(Ort::RunOptions{nullptr}, inputNames, inputTensors.data(), numInputNodes,
                        outputNames, outputTensors.data(), numOutputNodes);

            vector<float> prediction;
            if( outputTensorValues.at(0).size() == 1 ){
                prediction.push_back(1-outputTensorValues.at(0).at(0));
            }else{
                for (size_t i = 0; i < numOutputNodes; i++){
                    prediction.push_back(outputTensorValues.at(0).at(i));
                }
            }

            return prediction;

        }
};
