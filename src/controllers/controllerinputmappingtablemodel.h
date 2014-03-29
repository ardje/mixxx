#ifndef CONTROLLERINPUTMAPPINGTABLEMODEL_H
#define CONTROLLERINPUTMAPPINGTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>
#include <QAbstractItemDelegate>

#include "controllers/controllermappingtablemodel.h"
#include "controllers/midi/midimessage.h"

class ControllerInputMappingTableModel : public ControllerMappingTableModel {
    Q_OBJECT
  public:
    ControllerInputMappingTableModel(QObject* pParent);
    virtual ~ControllerInputMappingTableModel();

    // Apply the changes to the loaded preset.
    void apply();

    // Clears all input mappings in the preset.
    void clear();

    // Adds an empty input mapping.
    void addEmptyMapping();

    // Removes the provided input mappings.
    void removeMappings(QModelIndexList indices);

    // Returns a delegate for the provided column or NULL if the column does not
    // need a delegate.
    QAbstractItemDelegate* delegateForColumn(int column, QWidget* pParent);

    ////////////////////////////////////////////////////////////////////////////
    // QAbstractItemModel methods
    ////////////////////////////////////////////////////////////////////////////
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value,
                 int role = Qt::EditRole);

  protected:
    void onPresetLoaded();

  private:
    enum MidiColumn {
        MIDI_COLUMN_CHANNEL = 0,
        MIDI_COLUMN_OPCODE,
        MIDI_COLUMN_CONTROL,
        MIDI_COLUMN_OPTIONS,
        MIDI_COLUMN_ACTION,
        MIDI_COLUMN_COMMENT
    };

    QList<MidiInputMapping> m_midiInputMappings;
};

#endif /* CONTROLLERINPUTMAPPINGTABLEMODEL_H */