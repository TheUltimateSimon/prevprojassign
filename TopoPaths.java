// Simon Tran (si668612)
// COP 3503, Fall 2021

import java.util.*;
import java.io.*;

public class TopoPaths
{
  // Modified from the toposort.java from Dr. Szumlanski
  public static int countTopoPaths(String filename) throws FileNotFoundException
  {
    // The count for amount of topopath in this file and other variables.
    int topopath = 0, x, y;

    // Find the amount of vertices in the graph and set up the Graph
    // Using the amount of vertices is in this graph.
    Scanner in = new Scanner(new File(filename));
    int vertices = in.nextInt();
    Graph graph = new Graph(vertices);

    // Stolen from Dr. Szumlanski's toposort.java, create an array of 0s which
    // illustrate the amount of path to that every vertex.
    int[] incoming = new int[vertices];
    Arrays.fill(incoming, 0);

    // Cycle through all vertices.
    for (x = 0; x < vertices; x++)
    {
      // Find the amount of vertices for each line.
      int adjacent = in.nextInt();

      // For every adjacent, get the vertex and make an edge at the vertex.
      // Also add the amount of incoming edge to the adjacent vertex.
      for (y = 0; y < adjacent; y++)
      {
        int temp = in.nextInt();
        graph.addEdge(x, temp - 1);
        incoming[temp - 1] += 1;
      }
    }

    // Taken from Dr. Szumlanski's toposort.java, find the vertex that has
    // 0 edges coming toward them, then add it to the queue first.
    Queue<Integer> q = new ArrayDeque<Integer>();
    for (int i = 0; i < vertices; i++)
    {
      if (incoming[i] == 0)
        q.add(i);
    }

    // At this point, if the path does not have 1 vertex with 0 edges incoming,
    // then either the path has no starting point or atleast one vertex cannot be
    // met, as such the graph has no path.
    if (q.size() != 1)
      return 0;

    // A topo sort modified from Dr. Szumlanski's toposort.java
    int cnt = 0;
    while (!q.isEmpty())
    {
      int node = q.remove();
      cnt++;

      for (int i = 0; i < vertices; i++)
      {
        // If this vertex no longer has more path to it and it is adjacent to
        // the vertex node, then add it to the queue.
        if (graph.isAdjacency(node, i) && --incoming[i] == 0)
          q.add(i);
      }

      // When the path has all vertex, increase the amount of paths.
      if (cnt == vertices)
        topopath++;

      // If the queue becomes a cycle, remove the path from the path.
      if (cnt > vertices)
        topopath--;
    }

    // Returns the amount of path in this graph.
    return topopath;
  }


  // Setting the adjacent list graph was harder than making the matrix graph.
  // However, it is def much easier than the rest of the programs except
  // GenericBST.
  public static double difficultyRating()
  {
    return 1.5;
  }

  public static double hoursSpent()
  {
    return 2 + 7 + 3 + 7;
  }
}

class Graph
{
  // An ArrayList of ArrayList<Integer> that contains the adjacent vertices for
  // each vertex.
  ArrayList<ArrayList<Integer>> vertices;

  // A public constructor that set up the graph with the amount of vertices.
  public Graph(int vertices)
  {
    this.vertices = new ArrayList<ArrayList<Integer>>(vertices);
    for (int x = 0; x < vertices; x++)
    {
      this.vertices.add(new ArrayList<Integer>());
    }
  }

  // At a specific vertex, add the adjacent vertex for that vertex.
  public void addEdge(int vertex, int adjVertex)
  {
    this.vertices.get(vertex).add(adjVertex);
  }

  public boolean isAdjacency(int vertex, int differentVertex)
  {
    // Go through all the adjacent vertex.
    for (int i = 0; i < vertices.get(vertex).size(); i++)
    {
      // Check if the different Vertex matches of any adjacent vertex. If so,
      // return the different vertex is adjacent.
      if (vertices.get(vertex).get(i) == differentVertex)
        return true;
    }
    // The vertex is not adjacent.
    return false;
  }
}
