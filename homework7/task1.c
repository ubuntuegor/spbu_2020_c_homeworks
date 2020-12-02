#include "../library/graph/graph.h"
#include <stdio.h>

const char inputFilename[] = "hw7task1_input.txt";

int getStudentVariant(Graph* graph, int student)
{
    if (student >= 1 && student <= 3)
        return student;

    GraphNode** nextStudents = NULL;
    int nextStudentCount = getOutwardGraphConnections(graph, student, &nextStudents);

    // Isolated node means that the student has not passed.
    if (nextStudentCount == 0) {
        destroyGraphConnections(&nextStudents, nextStudentCount);
        return -1;
    }

    int nextStudent = getIdGraphNode(nextStudents[0]);

    destroyGraphConnections(&nextStudents, nextStudentCount);

    return getStudentVariant(graph, nextStudent);
}

void readStudentData(FILE* inputFile, Graph* graph, int studentCount)
{
    for (int i = 0; i < studentCount - 3; ++i) {
        int student = 0;
        int variant = 0;
        fscanf(inputFile, "%d %d", &student, &variant);

        if (variant != -1)
            connectGraph(graph, student, variant, 1);
    }
}

int main()
{
    printf("Reading input from %s\n", inputFilename);
    FILE* inputFile = fopen(inputFilename, "r");

    if (inputFile == NULL) {
        printf("Fail! Make sure this input file exists.\n");
        return 0;
    }

    int studentCount = 0;
    fscanf(inputFile, "%d", &studentCount);

    Graph* graph = createGraph(studentCount + 1, false);
    readStudentData(inputFile, graph, studentCount);

    fclose(inputFile);

    if (!isGraphAcyclic(graph)) {
        printf("Student graph contains cycles. Please check your input data.\n");
        return 0;
    }

    for (int i = 4; i <= studentCount; ++i) {
        int studentVariant = getStudentVariant(graph, i);
        if (studentVariant == -1)
            printf("Student %d should be expelled.\n", i);
        else
            printf("Student %d - %d\n", i, studentVariant);
    }

    destroyGraph(&graph);
    return 0;
}
