#include "SimpleMapView.hpp"
#include <iostream>
#include "ProjectR.Model/RMap.hpp"
#include "IModel.hpp"

namespace ProjectR
{
struct SimpleMapViewImpl
{
  SimpleMapViewImpl()
  {
  }

  void Show()
  {
    using namespace std;

    auto map = _model->GetMap();
    Rectangle heatZone = map->HeatZone();
    for(int row = heatZone.Top(); row < heatZone.Bottom(); ++row)
      {
        cout << endl;
        for(int col = heatZone.Left(); col < heatZone.Right(); ++col)
        {
            auto& cell = map->Get(row, col);
            char cellChar = ' ';
            if(cell & Wall)
              cellChar = '#';
            if(cell & Floor)
              cellChar = '.';
            if(cell & Door)
              cellChar = 'D';
            if(cell & Uncommon)
              cout << "\033[1;32m";
            if(cell & Rare)
              cout << "\033[1;34m";
            if(cell & Epic)
              cout << "\033[1;35m";
            if(cell & Legendary)
              cout << "\033[1;33m";
            if(cell & Artifact)
              cout << "\033[1;31;40m";
            if(cell & Small)
              cellChar = 'S';
            if(cell & Normal)
              cellChar = 'N';
            if(cell & Big)
              cellChar = 'B';
            if(cell & Grand)
              cellChar = 'G';

            cout << cellChar;
            cout << "\033[0m";
        }
    }
   cout << endl;
  }

  void Notify()
  {
    Show();
  }

  void SetModel(std::shared_ptr<IModel> model)
  {
    _model = model;
  }

  std::shared_ptr<IModel> _model;
};

SimpleMapView::SimpleMapView()
  : _(new SimpleMapViewImpl())
{
}

SimpleMapView::~SimpleMapView()
{
  delete _;
}

void SimpleMapView::Show()
{
  _->Show();
}

void SimpleMapView::SetModel(std::shared_ptr<IModel> model)
{
  _->SetModel(model);
}

void SimpleMapView::Notify()
{
  _->Notify();
}

}
