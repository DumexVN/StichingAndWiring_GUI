#include <QtGui>
#include <QColorDialog>

#include "vertex.h"
#include "propertiesdialog.h"

// --- PROPERTIES DIALOG FOR VERTEX ---
//Display properties information for vertices

PropertiesDialog::PropertiesDialog(Vertex *vertex, QWidget *parent)
    : QDialog(parent)
{   // --- SET UP THE UI FOR DIALOG ---
    //Constructing an additional dialog
    setupUi(this);

    this->vertex = vertex;
    xSpinBox->setRange(-1000,1000);
    ySpinBox->setRange(-1000,1000);
    xSpinBox->setValue(qreal(vertex->x()));
    ySpinBox->setValue(qreal(vertex->y()));
    textLineEdit->setText(vertex->name());
    outlineColor = vertex->outlineColor();
    backgroundColor = vertex->backgroundColor();

    updateColorLabel(outlineColorLabel, outlineColor);
    updateColorLabel(backgroundColorLabel, backgroundColor);
}

void PropertiesDialog::on_buttonBox_accepted()
{   // --- UPON CLICKING ---
    vertex->setPos(xSpinBox->value(), ySpinBox->value());
    vertex->setName(textLineEdit->text());
    vertex->setOutlineColor(outlineColor);
    vertex->setBackgroundColor(backgroundColor);
    vertex->update();
    QDialog::accept();
}


void PropertiesDialog::on_outlineColorButton_clicked()
{   // --- SETTING OUTLINE COLOUR ---
    chooseColor(outlineColorLabel, &outlineColor);
}

void PropertiesDialog::on_backgroundColorButton_clicked()
{   // --- SETTING BACKGROUND COLOUR ---
    chooseColor(backgroundColorLabel, &backgroundColor);
}

void PropertiesDialog::updateColorLabel(QLabel *label,
                                        const QColor &color)
{   // --- UPDATE COLOUR LABEL ---
    QPixmap pixmap(16, 16);
    pixmap.fill(color);
    label->setPixmap(pixmap);
}

void PropertiesDialog::chooseColor(QLabel *label, QColor *color)
{   // --- UPDATE COLOUR LABEL ---
    QColor newColor = QColorDialog::getColor(*color, this);
    if (newColor.isValid()) {
        *color = newColor;
        updateColorLabel(label, *color);
    }
}
