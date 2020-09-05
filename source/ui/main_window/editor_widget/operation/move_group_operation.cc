#include <ui/main_window/editor_widget/operation/move_group_operation.h>

/**
 * @brief		Constructor.
 */
EditorWidget::MoveGroupOperation::MoveGroupOperation(
    int oldIndex, int newIndex, EditorWidget *editorWidget) :
    OperationBase<EditorWidget::MoveGroupOperation, int, int, EditorWidget *>(
        editorWidget),
    m_oldIndex(oldIndex), m_newIndex(newIndex)
{
    this->setInitialized();
}

/**
 * @brief	Do operation.
 */
bool EditorWidget::MoveGroupOperation::doOperation()
{
    // Editor Widget.
    EditorWidget *editorWidget = dynamic_cast<EditorWidget *>(m_editorWidget);
    Q_ASSERT(editorWidget != nullptr);

    // Take group item.
    GroupItem *groupItem = dynamic_cast<GroupItem *>(
        editorWidget->m_itemGroups->takeChild(m_oldIndex));
    Q_ASSERT(groupItem != nullptr);

    // Insert group item.
    editorWidget->m_itemGroups->insertChild(m_newIndex, groupItem);
    GroupItemWidget *groupWidget = new GroupItemWidget(groupItem);
    groupWidget->connect(groupWidget, &GroupItemWidget::upBtnClicked,
                         editorWidget, &EditorWidget::onGroupMoveUp);
    groupWidget->connect(groupWidget, &GroupItemWidget::downBtnClicked,
                         editorWidget, &EditorWidget::onGroupMoveDown);
    groupWidget->connect(groupWidget, &GroupItemWidget::removeBtnClicked,
                         editorWidget, &EditorWidget::removeGroupItem);
    editorWidget->m_treeEditor->setItemWidget(groupItem, 1, groupWidget);

    // Set index.
    editorWidget->m_save->setIndex(m_oldIndex, m_newIndex);

    // Set module widgets.
    for (int i = 0; i < groupItem->childCount(); ++i) {
        ModuleItem *moduleItem = groupItem->child(i);

        ModuleItemWidget *moduleWidget = new ModuleItemWidget(moduleItem);
        moduleWidget->connect(moduleWidget, &ModuleItemWidget::upBtnClicked,
                              editorWidget, &EditorWidget::onModuleMoveUp);
        moduleWidget->connect(moduleWidget, &ModuleItemWidget::downBtnClicked,
                              editorWidget, &EditorWidget::onModuleMoveDown);
        moduleWidget->connect(moduleWidget, &ModuleItemWidget::removeBtnClicked,
                              editorWidget, &EditorWidget::removeModuleItem);

        editorWidget->m_treeEditor->setItemWidget(moduleItem, 1, moduleWidget);
    }

    // Update.
    editorWidget->updateGroupMoveButtonStatus(groupItem);

    if (groupItem->childCount() > 0) {
        editorWidget->updateModuleMoveButtonStatus(groupItem->child(0));
        editorWidget->updateModuleMoveButtonStatus(
            groupItem->child(groupItem->childCount() - 1));
    }

    if (editorWidget->m_itemGroups->childCount() > 0) {
        if (m_oldIndex == 0) {
            GroupItem *nextItem = dynamic_cast<GroupItem *>(
                editorWidget->m_itemGroups->child(0));
            Q_ASSERT(nextItem != nullptr);
            editorWidget->updateGroupMoveButtonStatus(nextItem);

        } else if (m_oldIndex >= editorWidget->m_itemGroups->childCount()) {
            GroupItem *prevItem = dynamic_cast<GroupItem *>(
                editorWidget->m_itemGroups->child(m_oldIndex - 1));
            Q_ASSERT(prevItem != nullptr);
            editorWidget->updateGroupMoveButtonStatus(prevItem);
        }
    }

    return true;
}

/**
 * @brief	Undo operation.
 */
void EditorWidget::MoveGroupOperation::undoOperation()
{
    // Editor Widget.
    EditorWidget *editorWidget = dynamic_cast<EditorWidget *>(m_editorWidget);
    Q_ASSERT(editorWidget != nullptr);

    // Take group item.
    GroupItem *groupItem = dynamic_cast<GroupItem *>(
        editorWidget->m_itemGroups->takeChild(m_newIndex));
    Q_ASSERT(groupItem != nullptr);

    // Insert group item.
    editorWidget->m_itemGroups->insertChild(m_oldIndex, groupItem);
    GroupItemWidget *groupWidget = new GroupItemWidget(groupItem);
    groupWidget->connect(groupWidget, &GroupItemWidget::upBtnClicked,
                         editorWidget, &EditorWidget::onGroupMoveUp);
    groupWidget->connect(groupWidget, &GroupItemWidget::downBtnClicked,
                         editorWidget, &EditorWidget::onGroupMoveDown);
    groupWidget->connect(groupWidget, &GroupItemWidget::removeBtnClicked,
                         editorWidget, &EditorWidget::removeGroupItem);
    editorWidget->m_treeEditor->setItemWidget(groupItem, 1, groupWidget);

    // Set index.
    editorWidget->m_save->setIndex(m_newIndex, m_oldIndex);

    // Set module widgets.
    for (int i = 0; i < groupItem->childCount(); ++i) {
        ModuleItem *moduleItem = groupItem->child(i);

        ModuleItemWidget *moduleWidget = new ModuleItemWidget(moduleItem);
        moduleWidget->connect(moduleWidget, &ModuleItemWidget::upBtnClicked,
                              editorWidget, &EditorWidget::onModuleMoveUp);
        moduleWidget->connect(moduleWidget, &ModuleItemWidget::downBtnClicked,
                              editorWidget, &EditorWidget::onModuleMoveDown);
        moduleWidget->connect(moduleWidget, &ModuleItemWidget::removeBtnClicked,
                              editorWidget, &EditorWidget::removeModuleItem);

        editorWidget->m_treeEditor->setItemWidget(moduleItem, 1, moduleWidget);
    }

    // Update.
    editorWidget->updateGroupMoveButtonStatus(groupItem);

    if (groupItem->childCount() > 0) {
        editorWidget->updateModuleMoveButtonStatus(groupItem->child(0));
        editorWidget->updateModuleMoveButtonStatus(
            groupItem->child(groupItem->childCount() - 1));
    }

    if (editorWidget->m_itemGroups->childCount() > 0) {
        if (m_newIndex == 0) {
            GroupItem *nextItem = dynamic_cast<GroupItem *>(
                editorWidget->m_itemGroups->child(0));
            Q_ASSERT(nextItem != nullptr);
            editorWidget->updateGroupMoveButtonStatus(nextItem);

        } else if (m_newIndex >= editorWidget->m_itemGroups->childCount()) {
            GroupItem *prevItem = dynamic_cast<GroupItem *>(
                editorWidget->m_itemGroups->child(m_newIndex - 1));
            Q_ASSERT(prevItem != nullptr);
            editorWidget->updateGroupMoveButtonStatus(prevItem);
        }
    }

    return;
}

/**
 * @brief	Destructor.
 */
EditorWidget::MoveGroupOperation::~MoveGroupOperation() {}
