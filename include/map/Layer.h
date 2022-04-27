#ifndef LAYER_H
#define LAYER_H
#include <string>
class Layer {
public:
  virtual void Render() = 0;
  virtual void Update() = 0;
  virtual void DeleteTile(const int &x, const int &y) = 0;
  virtual void Reset() = 0;
  inline std::string GetName() { return m_LayerName; }

protected:
  std::string m_LayerName;
};

#endif