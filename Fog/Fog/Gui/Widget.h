// [Fog-Gui Library - Public API]
//
// [Licence]
// MIT, See COPYING file in package

// [Guard]
#ifndef _FOG_GUI_WIDGET_H
#define _FOG_GUI_WIDGET_H

// [Dependencies]
#include <Fog/Core/Event.h>
#include <Fog/Core/Hash.h>
#include <Fog/Core/List.h>
#include <Fog/Core/Lock.h>
#include <Fog/Core/Misc.h>
#include <Fog/Core/Object.h>
#include <Fog/Core/Thread.h>
#include <Fog/Core/Time.h>
#include <Fog/Graphics/Font.h>
#include <Fog/Graphics/Geometry.h>
#include <Fog/Graphics/Painter.h>
#include <Fog/Gui/Constants.h>
#include <Fog/Gui/Event.h>
#include <Fog/Gui/Layout/LayoutItem.h>

//! @addtogroup Fog_Gui
//! @{

namespace Fog {

// ============================================================================
// [Forward Declarations]
// ============================================================================

struct Layout;
struct GuiEngine;
struct GuiWindow;
struct Widget;
struct Window;

// ============================================================================
// [Fog::Widget]
// ============================================================================

//! @brief Base class for creating visual components that can be painted on the 
//! screen and that can catch events generated by windowing system.
//!
//! @c Fog::Widget is based on @c Fog::LayoutItem and layout item is based 
//! on @c Fog::Object. Layout item allows to very easy set or calculate layout 
//! metrics for each widget. And @c Fog::Object allows to use event mechanism
//! and object introspection that's implemented in Core library.
//!
//! @c Fog::Widget event base is a lot increased compared to @c Fog::Object. It 
//! contains these new event handlers:
//!  - <code>virtual void onStateChange(StateEvent* e)</code>
//!  - <code>virtual void onVisibilityChange(VisibilityEvent* e)</code>
//!  - <code>virtual void onConfigure(ConfigureEvent* e)</code>
//!  - <code>virtual void onFocus(FocusEvent* e)</code>
//!  - <code>virtual void onKey(KeyEvent* e)</code>
//!  - <code>virtual void onMouse(MouseEvent* e)</code>
//!  - <code>virtual void onNcPaint(PaintEvent* e)</code>
//!  - <code>virtual void onPaint(PaintEvent* e)</code>
//!  - <code>virtual void onClose(CloseEvent* e)</code>
//!
//! Widget state:
//!
//! Widget visibility is controled by @c StateEvent and can be changed 
//! via @c setState(), @c enable() and @c disable() methods. To check 
//! if widget is enabled use @c state() method.
//!
//! Widget visibility:
//!
//! Widget visibility is controled by @c VisibilityEvent and can be changed 
//! via @c setVisibility(), @c show() and @c hide() methods. To check if widget
//! is visible use @c visibility() method.
//!
//! Widget geometry:
//!
//! Widget geometry is most important thing for widgets. Widget position and size
//! is represented by @c Fog::Rect structure and can be retrieved by @c rect() method.
//! Coordinates that's retrieved represents widget position that's relative to it's
//! parent. If widget parent is @c NULL then this position is relative to the screen
//! coordinates (desktop window).
struct FOG_API Widget : public LayoutItem
{
  FOG_DECLARE_OBJECT(Widget, LayoutItem)

  // --------------------------------------------------------------------------
  // [Construction / Destruction]
  // --------------------------------------------------------------------------

  Widget(uint32_t createFlags = 0);
  virtual ~Widget();

  // --------------------------------------------------------------------------
  // [Hierarchy]
  // --------------------------------------------------------------------------

  //! @brief Get whether the widget is root.
  FOG_INLINE bool isRoot() const { return _parent == NULL; }

  //! @brief Get whether the widget has parent.
  FOG_INLINE bool hasParent() const { return _parent != NULL; }

  //! @brief Get whether the widget has children.
  FOG_INLINE bool hasChildren() const { return !_children.isEmpty(); }

  //! @brief Get widget parent.
  FOG_INLINE Widget* getParent() const { return _parent; }

  //! @brief Get widget children.
  FOG_INLINE List<Widget*> getChildren() const { return _children; }

  //! @brief Set parent of this widget to @a p.
  bool setParent(Widget* p);
  //! @brief Add widget @a w into the widget.
  bool add(Widget* w);
  //! @brief Remove widget @a w from the widget.
  bool remove(Widget* w);

  //! @brief Add widget at specified index.
  //!
  //! This method can be overriden to improve child widgets management. It can
  //! be called throught @c setParent(), @a add() and @c remove() methods.
  virtual bool _add(sysuint_t index, Widget* w);

  //! @brief Remove widget at specified index.
  //!
  //! This method can be overriden to improve child widgets management. It can
  //! be called throught @c setParent(), @a add() and @c remove() methods.
  virtual bool _remove(sysuint_t index, Widget* w);

  // --------------------------------------------------------------------------
  // [GuiWindow]
  // --------------------------------------------------------------------------

  //! @brief Get whether widget has native gui window (@c GuiWindow).
  FOG_INLINE bool isGuiWindow() const { return _guiWindow != NULL; }

  //! @brief Get native gui window (only for top-level widgets).
  FOG_INLINE GuiWindow* getGuiWindow() const { return _guiWindow; }

  //! @brief Get closest native gui window.
  //!
  //! Returns gui window associated with this widget. If this widget hasn't
  //! gui window then all parents are traversed until it's found, otherwise
  //! @c NULL is returned.
  GuiWindow* getClosestGuiWindow() const;

  //! @brief Create native gui window.
  err_t createWindow(uint32_t createFlags = 0);
  //! @brief Destroy native gui window.
  err_t destroyWindow();

  //! @brief Get native gui window title.
  String getWindowTitle() const;
  //! @brief Set native gui window title.
  err_t setWindowTitle(const String& title);

  //! @brief Get native gui window icon.
  Image getWindowIcon() const;
  //! @brief Set native gui window icon.
  err_t setWindowIcon(const Image& icon);

  //! @brief Get native gui window resize granularity.
  Point getWindowGranularity() const;
  //! @brief Set native gui window resize granularity.
  err_t setWindowGranularity(const Point& pt);

  // --------------------------------------------------------------------------
  // [Geometry]
  // --------------------------------------------------------------------------

  //! @brief Get widget geometry.
  FOG_INLINE const Rect& getGeometry() const { return _geometry; }
  //! @brief Get widget position relative to parent.
  FOG_INLINE const Point& getPosition() const { return _geometry.getPosition(); }
  //! @brief Get widget size.
  FOG_INLINE const Size& getSize() const { return _geometry.getSize(); }

  //! @brief Get widget left position, this method is equal to @c left().
  FOG_INLINE int getX() const { return _geometry.x; }
  //! @brief Get widget top position, this method is equal to @c top().
  FOG_INLINE int getY() const { return _geometry.y; }
  //! @brief Get widget width.
  FOG_INLINE int getWidth() const { return _geometry.w; }
  //! @brief Get widget height.
  FOG_INLINE int getHeight() const { return _geometry.h; }

  //! @brief Get widget client geometry.
  FOG_INLINE const Rect& getClientGeometry() const { return _clientGeometry; }
  //! @brief Get widget position relative to parent.
  FOG_INLINE const Point& getClientPosition() const { return _clientGeometry.getPosition(); }
  //! @brief Get widget size.
  FOG_INLINE const Size& getClientSize() const { return _clientGeometry.getSize(); }

  //! @brief Get widget left position, this method is equal to @c left().
  FOG_INLINE int getClientX() const { return _clientGeometry.x; }
  //! @brief Get widget top position, this method is equal to @c top().
  FOG_INLINE int getClientY() const { return _clientGeometry.y; }
  //! @brief Get widget width.
  FOG_INLINE int getClientWidth() const { return _clientGeometry.w; }
  //! @brief Get widget height.
  FOG_INLINE int getClientHeight() const { return _clientGeometry.h; }

  //! @brief Get widget origin.
  FOG_INLINE const Point& getOrigin() const { return _origin; }

  //! @brief Set widget position and size to @a geometry.
  void setGeometry(const Rect& geometry);

  //! @brief Set widget position to @a pt.
  //!
  //! @note To set widget position and size together use @c setGeometry().
  void setPosition(const Point& pt);

  //! @brief Set the widget size to @a sz.
  //!
  //! @note To set widget position and size together use @c setGeometry().
  void setSize(const Size& size);

  //! @brief Set widget origin to @a pt.
  void setOrigin(const Point& pt);

  //! @brief Set widget position to @a pt.
  //!
  //! This method is similar to @c setPosition().
  FOG_INLINE void move(const Point& pt) { setPosition(pt); }

  //! @brief Set widget size to @a size.
  //!
  //! This method is similar to @c setSize().
  FOG_INLINE void resize(const Size& size) { setSize(size); }

  //! @brief Translate world coordinate @a coord into client (relative to the
  //! widget).
  bool worldToClient(Point* coord) const;

  //! @brief Translate client coordinate @a coord into world (relative to the
  //! screen).
  bool clientToWorld(Point* coord) const;

  //! @brief Translate coordinates between two widgets.
  static bool translateCoordinates(Widget* to, Widget* from, Point* coords);

  // --------------------------------------------------------------------------
  // [Hit Testing]
  // --------------------------------------------------------------------------

  Widget* hitTest(const Point& pt) const;
  Widget* getChildAt(const Point& pt, bool recursive = false) const;

  // --------------------------------------------------------------------------
  // [Layout Of Widget]
  // --------------------------------------------------------------------------

  //! @brief Get widget layout manager.
  FOG_INLINE Layout* getLayout() const { return _layout; }

  //! @brief Set widget layout manager.
  void setLayout(Layout* layout);

  //! @brief Delete widget layout manager (will first disconnects children).
  void deleteLayout();

  //! @brief Take widget layout manager (will not disconnect children).
  Layout* takeLayout();

  // --------------------------------------------------------------------------
  // [Layout Hints]
  // --------------------------------------------------------------------------

  virtual const LayoutHint& getLayoutHint() const;
  virtual void setLayoutHint(const LayoutHint& layoutHint);

  virtual const LayoutHint& getComputedLayoutHint() const;
  virtual void computeLayoutHint();

  // --------------------------------------------------------------------------
  // [Layout Policy]
  // --------------------------------------------------------------------------

  virtual uint32_t getLayoutPolicy() const;
  virtual void setLayoutPolicy(uint32_t policy);

  // --------------------------------------------------------------------------
  // [Layout Height For Width]
  // --------------------------------------------------------------------------

  virtual bool hasHeightForWidth() const;
  virtual int getHeightForWidth(int width) const;

  // --------------------------------------------------------------------------
  // [Layout State]
  // --------------------------------------------------------------------------

  virtual bool isLayoutDirty() const;
  virtual void invalidateLayout() const;

  // --------------------------------------------------------------------------
  // [Widget State]
  // --------------------------------------------------------------------------

  //! @brief Get widget state, see @c WIDGET_STATE.
  FOG_INLINE uint32_t getState() const { return _state; }
  //! @brief Get whether widget is enabled.
  FOG_INLINE bool isEnabled() const { return _state == WIDGET_ENABLED; }
  //! @brief Get whether widget is enabled to parent.
  FOG_INLINE bool isEnabledToParent() const { return _state != WIDGET_DISABLED; }

  //! @brief Set widget state to @a val.
  void setEnabled(bool val = true);

  //! @brief Set widget state to @c WIDGET_ENABLED.
  FOG_INLINE void enable() { setEnabled(true); }
  //! @brief Set widget state to @c WIDGET_DISABLED.
  FOG_INLINE void disable() { setEnabled(false); }

  // --------------------------------------------------------------------------
  // [Widget Visibility]
  // --------------------------------------------------------------------------

  //! @brief Returns widget visibility, see @c Visibility_Enum.
  FOG_INLINE uint32_t getVisibility() const { return _visibility; }

  //! @brief Get whether widget is visible.
  FOG_INLINE bool isVisible() const { return _visibility == WIDGET_VISIBLE; }
  //! @brief Get whether widget is visible to parent.
  FOG_INLINE bool isVisibleToParent() const { return _state != WIDGET_HIDDEN; }

  //! @brief Set widget visibility to @a val.
  void setVisible(bool val = true);
  
  //! @brief Show widget (set it's visibility to true).
  FOG_INLINE void show() { setVisible(true); }
  //! @brief Show widget (set it's visibility to false).
  FOG_INLINE void hide() { setVisible(false); }

  // --------------------------------------------------------------------------
  // [Widget Orientation]
  // --------------------------------------------------------------------------

  //! @brief Returns widget orientation, see @c OrientationEnum.
  FOG_INLINE uint32_t orientation() const { return _orientation; }

  //! @brief Returns @c true if widget orientation is horizontal (default).
  FOG_INLINE bool isHorizontal() const { return orientation() == ORIENTATION_HORIZONTAL; }

  //! @brief Returns @c true if widget orientation is vertical.
  FOG_INLINE bool isVertical() const { return orientation() == ORIENTATION_VERTICAL; }

  //! @brief Sets widget orientation.
  void setOrientation(uint32_t val);

  //! @brief Sets widget orientation to horizontal (@c OrientationHorizontal).
  FOG_INLINE void setHorizontal() { setOrientation(ORIENTATION_HORIZONTAL); }

  //! @brief Sets widget orientation to vertical (@c OrientationVertical).
  FOG_INLINE void setVertical()  { setOrientation(ORIENTATION_VERTICAL); }

  // --------------------------------------------------------------------------
  // [Caret]
  // --------------------------------------------------------------------------

  // bool showCaret();
  // bool showCaret(const CaretProperties& properties);
  // bool hideCaret();

  // --------------------------------------------------------------------------
  // [Tab Order]
  // --------------------------------------------------------------------------

  //! @brief Returns widget tab order.
  FOG_INLINE int getTabOrder() const { return _tabOrder; }

  //! @brief Sets widget tab order.
  void setTabOrder(int tabOrder);

  // --------------------------------------------------------------------------
  // [Focus]
  // --------------------------------------------------------------------------

  FOG_INLINE uint32_t getFocusPolicy() const { return _focusPolicy; }

  void setFocusPolicy(uint32_t val);

  FOG_INLINE bool hasFocus() const { return _hasFocus; }

  virtual Widget* getFocusableWidget(int focusable);

  //! @brief Takes client focus for this widget.
  void takeFocus(uint32_t reason = FOCUS_REASON_NONE);

  void giveFocusNext(uint32_t reason = FOCUS_REASON_NONE);
  void giveFocusPrevious(uint32_t reason = FOCUS_REASON_NONE);

  Widget* _findFocus() const;

  // --------------------------------------------------------------------------
  // [Font]
  // --------------------------------------------------------------------------

  //! @brief Get widget font.
  FOG_INLINE Font getFont() const { return _font; }

  //! @brief Set widget font.
  void setFont(const Font& font);

  // --------------------------------------------------------------------------
  // [Update]
  // --------------------------------------------------------------------------

  //! @brief Update widget (see @c WIDGET_UPDATE_FLAGS).
  void update(uint32_t updateFlags);

  // --------------------------------------------------------------------------
  // [Painting]
  // --------------------------------------------------------------------------

  //! @brief Repaint widget, see @c WIDGET_REPAINT_FLAGS.
  void repaint(uint32_t repaintFlags);

  //! @brief Get paint hints, see @c WIDGET_PAINT_MODE.
  //!
  //! Paint hints are used to optimize widget repainting process. Each widget
  //! must be paint when it's displayed on the screen. There are widgets that
  //! usually repaint the entire area (@c TextBox, @c TextArea, @c ToolBar, etc)
  //! and there are widgets that in most cases need the background provided by
  //! parent (very good example is @c Label).
  //!
  //! Use @c getPaintHint() to tell Fog-Gui how the widget will be updated.
  //! Default return value is @c WIDGET_PAINT_SCREEN which means that entire
  //! widget will be updated (result is not based on parent content). If you
  //! need to draw rounded corners or to content paint previously by parent,
  //! use @c WIDGET_PAINT_PROPAGATED hint.
  //!
  //! If you return @c WIDGET_PAINT_PROPAGATED then the gui engine always call
  //! the @c Widget::getPropagatedRegion() method to get which region will be
  //! propagated. You don't need to reimplement this method (it will return the
  //! whole widget region by default). If you want to draw only rounded corners
  //! or something that will overpaint only very small area, you can reimplement
  //! this method to optimize painting process.
  virtual uint32_t getPaintHint() const;

  //! @brief Get region that will be propagated from parent to the @c onPaint()
  //! event handler.
  //!
  //! Default action is to return the entire widget region. If an error is
  //! returned then gui engine will generate the whole region automatically
  //! (but never return just error, it will be probably logged to stderr).
  virtual err_t getPropagatedRegion(Region* dst) const;

  // --------------------------------------------------------------------------
  // [Event Handlers]
  // --------------------------------------------------------------------------

  //! @brief Child event handler.
  virtual void onChildAdd(ChildEvent* e);
  //! @brief Child event handler.
  virtual void onChildRemove(ChildEvent* e);
  //! @brief State event handler.
  virtual void onEnable(StateEvent* e);
  //! @brief State event handler.
  virtual void onDisable(StateEvent* e);
  //! @brief Visibility event handler.
  virtual void onShow(VisibilityEvent* e);
  //! @brief Visibility event handler.
  virtual void onHide(VisibilityEvent* e);
  //! @brief Configure event handler.
  virtual void onConfigure(ConfigureEvent* e);
  //! @brief Focus in event handler.
  virtual void onFocusIn(FocusEvent* e);
  //! @brief Focus out event handler.
  virtual void onFocusOut(FocusEvent* e);
  //! @brief Keyboard event handler.
  virtual void onKeyPress(KeyEvent* e);
  //! @brief Keyboard event handler.
  virtual void onKeyRelease(KeyEvent* e);
  //! @brief Mouse in event handler.
  virtual void onMouseIn(MouseEvent* e);
  //! @brief Mouse out event handler.
  virtual void onMouseOut(MouseEvent* e);
  //! @brief Mouse moveevent handler.
  virtual void onMouseMove(MouseEvent* e);
  //! @brief Mouse press event handler.
  virtual void onMousePress(MouseEvent* e);
  //! @brief Mouse release event handler.
  virtual void onMouseRelease(MouseEvent* e);
  //! @brief Click event handler.
  virtual void onClick(MouseEvent* e);
  //! @brief Double click event handler.
  virtual void onDoubleClick(MouseEvent* e);
  //! @brief Wheel event handler.
  virtual void onWheel(MouseEvent* e);
  //! @brief Selection event handler.
  virtual void onSelection(SelectionEvent* e);

  //! @brief Client paint handler.
  virtual void onPaint(PaintEvent* e);

  //! @brief Close event handler.
  virtual void onClose(CloseEvent* e);

  //! @brief Theme changed event handler.
  virtual void onThemeChange(ThemeEvent* e);

  //! @brief @c LayoutItem event handler.
  virtual void onLayout(LayoutEvent* e);

  // --------------------------------------------------------------------------
  // [Event Map]
  // --------------------------------------------------------------------------

  FOG_EVENT_BEGIN()
    FOG_EVENT_DEF(EVENT_CHILD_ADD           , onChildAdd        , ChildEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_CHILD_REMOVE        , onChildRemove     , ChildEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_ENABLE              , onEnable          , StateEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_DISABLE             , onDisable         , StateEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_DISABLE_BY_PARENT   , onDisable         , StateEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_SHOW                , onShow            , VisibilityEvent, OVERRIDE)
    FOG_EVENT_DEF(EVENT_HIDE                , onHide            , VisibilityEvent, OVERRIDE)
    FOG_EVENT_DEF(EVENT_HIDE_BY_PARENT      , onHide            , VisibilityEvent, OVERRIDE)
    FOG_EVENT_DEF(EVENT_CONFIGURE           , onConfigure       , ConfigureEvent , OVERRIDE)
    FOG_EVENT_DEF(EVENT_FOCUS_IN            , onFocusIn         , FocusEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_FOCUS_OUT           , onFocusOut        , FocusEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_KEY_PRESS           , onKeyPress        , KeyEvent       , OVERRIDE)
    FOG_EVENT_DEF(EVENT_KEY_RELEASE         , onKeyRelease      , KeyEvent       , OVERRIDE)
    FOG_EVENT_DEF(EVENT_MOUSE_IN            , onMouseIn         , MouseEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_MOUSE_OUT           , onMouseOut        , MouseEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_MOUSE_MOVE          , onMouseMove       , MouseEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_MOUSE_PRESS         , onMousePress      , MouseEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_MOUSE_RELEASE       , onMouseRelease    , MouseEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_CLICK               , onClick           , MouseEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_DOUBLE_CLICK        , onDoubleClick     , MouseEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_WHEEL               , onWheel           , MouseEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_CLEAR_SELECTION     , onSelection       , SelectionEvent , OVERRIDE)
    FOG_EVENT_DEF(EVENT_SELECTION_REQUIRED  , onSelection       , SelectionEvent , OVERRIDE)
    FOG_EVENT_DEF(EVENT_PAINT               , onPaint           , PaintEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_CLOSE               , onClose           , CloseEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_THEME               , onThemeChange     , ThemeEvent     , OVERRIDE)
    FOG_EVENT_DEF(EVENT_LAYOUT_SET          , onLayout          , LayoutEvent    , OVERRIDE)
    FOG_EVENT_DEF(EVENT_LAYOUT_REMOVE       , onLayout          , LayoutEvent    , OVERRIDE)
  FOG_EVENT_END()

  // --------------------------------------------------------------------------
  // [Members]
  // --------------------------------------------------------------------------

protected:
  Widget* _parent;

  List<Widget*> _children;

  //! @brief Native window data.
  GuiWindow* _guiWindow;

  //! @brief Main geometry (geometry relative to widget parent or screen).
  Rect _geometry;
  //! @brief Client area geometry (geometry within the widget).
  Rect _clientGeometry;
  //! @brief Client origin.
  Point _origin;

  //! @brief Font (used to draw text in widget).
  Font _font;

  //! @brief Layout.
  Layout* _layout;

  //! @brief Layout hints.
  LayoutHint _layoutHint;

  //! @brief Layout policy.
  uint8_t _layoutPolicy;
  //! @brief Whether the widget can trade height for width.
  bool _hasHeightForWidth;
  //! @brief Whether the layout is dirty (must be recalculated for this widget
  //! and all descendents).
  mutable bool _isLayoutDirty;

  //! @brief Tab order.
  int _tabOrder;

  //! @brief Link to child that was last focus.
  Widget* _lastFocus;
  Widget* _focusLink;

  //! @brief Update flags.
  uint32_t _uflags;

  //! @brief Widget state.
  uint32_t _state : 2;
  //! @brief Widget visibility.
  uint32_t _visibility : 2;
  //! @brief Widget focus policy
  uint32_t _focusPolicy : 4;
  //! @brief Focus.
  uint32_t _hasFocus : 1;
  //! @brief Widget orientation
  uint32_t _orientation : 1;
  //! @brief Reserved for future use.
  uint32_t _reserved : 22;

private:
  friend struct Application;
  friend struct BaseGuiEngine;
  friend struct BaseGuiWindow;
  friend struct GuiEngine;
  friend struct GuiWindow;
  friend struct Window;

  FOG_DISABLE_COPY(Widget)
};

} // Fog namespace

//! @}

// [Guard]
#endif // _FOG_GUI_WIDGET_H