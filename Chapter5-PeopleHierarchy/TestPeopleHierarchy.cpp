/////////////////////////////////////////////////////////////////////
// TestPeopleHierarchy.cpp - demonstrates hierarchy in action      //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ    //
/////////////////////////////////////////////////////////////////////

#ifdef TEST_HIERARCHY

#include <vector>
#include "SW_Eng.h"
#include "Dev.h"
#include "TeamLead.h"
#include "ProjMgr.h"

namespace Chap4 {

  using ProjectName = std::string;
  using TeamName = std::string;
  using Team = std::pair<TeamName, std::vector<SW_Eng*>>;
  using ProjectStaff = std::vector<Team>;
  using Project = std::tuple<ProjectName, ProjMgr, ProjectStaff>;

  void showTeam(Team& team) {
    std::cout << "\n  Team " << team.first;
    for (auto pSweng : team.second)
      std::cout << "\n    " << pSweng->nameAndTitle();
  }
  void showProject(Project& prj) {
    auto [prjName, prjMgr, staff] = prj;
    std::cout << "\n  " << prjName;
    std::cout << "\n  " << prjMgr.nameAndTitle();
    for (auto team : staff) {
      showTeam(team);
    }
  }
}

int main() {
  using namespace Chap4;

  ProjMgr Devin({ "Devin", "Project Manager", 45 });

  TeamLead Jill({ "Jill", "Team Lead & Web dev", 32 });
  Dev Jack({ "Jack", "UI dev", 28 });
  Dev Zhang({ "Zhang", "System dev", 37 });
  Dev Charley({ "Charley", "QA dev", 27 });
  Team FrontEnd{ "FrontEnd", { &Jill, &Jack, &Zhang, &Charley } };

  TeamLead Tom({ "Tom", "Team Lead & Backend Dev", 38 });
  Dev Ming({ "Ming", "Comm dev", 26 });
  Dev Sonal({ "Sonal", "Server dev", 27 });
  Team BackEnd{ "BackEnd", { &Tom, &Ming, &Sonal } };

  Project ProductX{ "ProductX", Devin, { FrontEnd, BackEnd } };

  showProject(ProductX);
  std::cout << std::endl;

  std::cout << "\n  Team " << FrontEnd.first << " at work";
  for (auto pDev : FrontEnd.second) {
    pDev->doWork();
    pDev->attendMeeting();
  }
  std::cout << std::endl;

  std::cout << "\n  Project Manager " << Devin.nameAndTitle() << " at work";
  Devin.doWork();
  Devin.attendMeeting();

  std::cout << "\n\n";
}

#endif
