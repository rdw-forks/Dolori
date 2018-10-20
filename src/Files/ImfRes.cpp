#include "Files/ImfRes.h"

#include "Common/debug.h"
#include "Files/File.h"

CImfRes::CImfRes() : m_ImfData(), m_maxAction(), m_maxMotion() {}

bool CImfRes::Load(const std::string& filename) {
  CFile file;

  if (!file.Open(filename, 0)) {
    LOG(error, "Failed to find file: {}", filename);
    return false;
  }

  float version;
  file.Read(&version, sizeof(version));

  if (version < 1.01f) {
    LOG(error, "Format version not supported: {}", filename);
    return false;
  }

  int32_t sum;
  file.Read(&sum, sizeof(sum));

  int32_t max_layer;
  file.Read(&max_layer, sizeof(max_layer));

  m_ImfData.resize(max_layer);
  for (int layer = 0; layer < max_layer; layer++) {
    int32_t num_actions;
    file.Read(&num_actions, sizeof(num_actions));

    for (int action = 0; action < num_actions; action++) {
      int32_t num_motions;
      file.Read(&num_motions, sizeof(num_motions));

      ImfData imf_data;

      for (int motion = 0; motion < num_motions; motion++) {
        struct {
          int32_t priority, cx, cy;
        } imf_data_block;

        file.Read(&imf_data_block, sizeof(imf_data_block));
        imf_data.priority.push_back(imf_data_block.priority);
        imf_data.cx.push_back(imf_data_block.cx);
        imf_data.cy.push_back(imf_data_block.cy);
      }

      m_ImfData[layer].push_back(imf_data);
    }
  }

  file.Close();

  return true;
}

CRes* CImfRes::Clone() { return new CImfRes(); }

glm::i32vec2 CImfRes::GetPoint(size_t layer, size_t action,
                               size_t motion) const {
  if (m_ImfData.size() <= layer || m_ImfData[layer].size() <= action) {
    return {};
  }

  const auto& imf_data = m_ImfData[layer][action];
  if (imf_data.cx.size() <= motion || imf_data.cy.size() <= motion) {
    return {};
  }

  return {imf_data.cx[motion], imf_data.cy[motion]};
}

void CImfRes::Reset() {}
