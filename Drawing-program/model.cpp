#include "model.h"
/* external libraries */
#include <iostream>

Model::Model() {
    Graph = TF_NewGraph();
    Status = TF_NewStatus();
    SessionOpts = TF_NewSessionOptions();
    RunOpts = NULL;
    ntags = 1;
}

Model::~Model() {
    // free memory
    TF_DeleteGraph(Graph);
    TF_DeleteSession(Session, Status);
    TF_DeleteSessionOptions(SessionOpts);
    TF_DeleteStatus(Status);
}

int Model::init() {
	std::cout << "TensorFlow Version: " << TF_Version() << std::endl;
    Session = TF_LoadSessionFromSavedModel(SessionOpts, RunOpts, model_path, &tags, ntags, Graph, NULL, Status);
    if (TF_GetCode(Status) != TF_OK) {
        std::cout << "TensorFlow failed to load model... Message: " << TF_Message(Status) << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
