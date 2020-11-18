#include "../library/graph/graph.h"
#include <stdio.h>

const char inputFilename[] = "hw7task1_input.txt";

int getStudentVariant(Graph* graph, int student)
{
    if (student >= 0 && student <= 3)
        return student;
    GraphNode** nextStudents = NULL;
    int nextStudentCount = getOutwardGraphConnections(graph, student, &nextStudents);

    if (nextStudentCount != 1) {
        destroyGraphConnections(&nextStudents, nextStudentCount);
        return -1;
    }

    int nextStudent = getIdGraphNode(nextStudents[0]);
    destroyGraphConnections(&nextStudents, nextStudentCount);

    return getStudentVariant(graph, nextStudent);
}

int main()
{
    printf("Reading input from %s\n", inputFilename);
    FILE* inputFile = fopen(inputFilename, "r");

    if (inputFile == NULL) {
        printf("Fail! Make sure this input file exists.\n");
        return 0;
    }

    int stundentCount = 0;
    fscanf(inputFile, "%d", &stundentCount);

    Graph* graph = createGraph(stundentCount + 1, false);

    for (int i = 0; i < stundentCount - 3; ++i) {
        int student = 0;
        int variant = 0;
        fscanf(inputFile, "%d %d", &student, &variant);

        if (variant == -1)
            variant = 0;
        connectGraph(graph, student, variant, 1);
    }

    fclose(inputFile);

    if (!isGraphAcyclic(graph)) {
        printf("Student graph contains cycles. Please check your input data.\n");
        return 0;
    }

    for (int i = 4; i <= stundentCount; ++i) {
        int studentVariant = getStudentVariant(graph, i);
        if (studentVariant == -1) {
            printf("Student %d has none or mixed information. Please check your input data.\n", i);
            continue;
        }
        if (studentVariant == 0)
            printf("Student %d should be expelled.\n", i);
        else
            printf("Student %d - %d\n", i, studentVariant);
    }

    destroyGraph(&graph);
    return 0;
}
