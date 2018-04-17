#include "stdafx.h"

template<class PGraph> 
void PrintGraphStat(const PGraph& G) {
  PGraph WCC = TSnap::GetMxWcc(G);
  PGraph SCC = TSnap::GetMxScc(G);
  TFltPrV DegCCfV;
  int64 ClosedTriads, OpenTriads;
  int FullDiam;
  double EffDiam;
  printf("Nodes,Edges,Nodes in largest WCC,Edges in largest WCC,Nodes in largest SCC,Edges in largest SCC,Average clustering coefficient,Number of triangles,Fraction of closed triangles,Diameter (longest shortest path),90-percentile effective diameter\n");
  printf("%d,", G->GetNodes());
  printf("%d,", G->GetEdges());
  printf("%d (%.3f),", WCC->GetNodes(), WCC->GetNodes()/double(G->GetNodes()));
  printf("%d (%.3f),", WCC->GetEdges(), WCC->GetEdges()/double(G->GetEdges()));
  printf("%d (%.3f),", SCC->GetNodes(), SCC->GetNodes()/double(G->GetNodes()));
  printf("%d (%.3f),", SCC->GetEdges(), SCC->GetEdges()/double(G->GetEdges()));
  const double CCF = TSnap::GetClustCf(G, DegCCfV, ClosedTriads, OpenTriads);
  printf("%.4f,", CCF);
  printf("%s,", TUInt64(ClosedTriads).GetStr().CStr());
  printf("%.4g,", ClosedTriads/double(ClosedTriads+OpenTriads));
  TSnap::GetBfsEffDiam(G, 1000, false, EffDiam, FullDiam);
  printf("%d,", FullDiam);
  printf("%.2g", EffDiam);
  printf("\n");
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
	printf("usage: feature_csv <graph file>\n");
	return 1;
  }
  PUNGraph G = TSnap::LoadEdgeList<PUNGraph>(argv[1], 0, 1, ' ');
  PrintGraphStat(G);
  return 0;
}
