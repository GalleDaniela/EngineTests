#pragma once
#include <vector>

class IEngine
{
public:
  IEngine(double iAmbientT, double iOverheatingT);

  virtual void UpdateState(double iDeltaTime) = 0;
  void Reset();

  double GetOverheatingT() const;
  double GetCurrentT() const;
  double GetCurrentV() const;
  double GetCurrentM() const;
  double GetCurrentN() const;

protected:
  double m_ambientT{ 0.0 }; // ����������� �����

  double m_currentT{ 0.0 };
  double m_currentV{ 0.0 };
  double m_currentM{ 0.0 };
  double m_currentN{ 0.0 };
  double m_overheatingT{ 100.0 }; //����������� ���������
};

class InternalCombustionEngine : public IEngine //����� ����������� ������ ���� ���������, ������� ��� ����������� ��������� � ������������� ����� UpdateState
{
public:
  InternalCombustionEngine(double iAmbientT, double iI, double iOverheatingT, double iHm, double iHv, double iC, const std::vector<std::pair<double, double>>& iMVDependency);

  void UpdateState(double iDeltaTime) override;

private:
  double m_I{ 1.0 }; //������ �������
  double m_Hm{ 1.0 }; //����������� ����������� �������� ������� �� ��������� �������
  double m_Hv{ 1.0 }; //����������� ����������� �������� ������� �� �������� �������� ���������
  double m_C{ 1.0 }; //����������� ����������� �������� ���������� �� ����������� ��������� � ���������� �����
  std::vector<std::pair<double, double>> m_MVDependency{}; //�������-�������� ����������� ������� M �� �������� V
};

