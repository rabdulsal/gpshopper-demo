//
//  SCPopup.h
//  lunds
//
//  Created by kimberly on 8/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 SCPopup displays a view inside another view.
 
 Its subclasses display the view in various ways.
 
 Note that popupView can be anything.  Consider for:
 
  - Loading indicators
  - Small input forms
 */
@interface SCPopup : NSObject

/**
 The view to be displayed.
 */
@property (retain) UIView *popupView;

/**
 The view inside which popupView is displayed.
 
 By default, this is the view of the rootViewController.
 
 Consider setting this to the view of the current view controller.
 */
@property (assign) UIView *containingView;

/**
 Shows popupView.
 */
-(void)show;

/**
 Hides popupView.
 */
-(void)dismiss;

@end


/**
 Displays a view scrolling up from the bottom of the containing view.
 */
@interface SCKeyboardStylePopup : SCPopup
@end


/**
 Displays a view inside a rounded rectangle in the middle of the containing view.
 
 Example:
 
     // Assume loadingPopup (SCPopup *) and loadingView (UIView *)
     // have been created elsewhere in the code or in a xib file.
 
     -(void)setSearchSpecs: (SCSearchSpecs *)s;
     {
         // ...
 
         [loadingPopup setPopupView: loadingView];
         [loadingPopup setContainingView: [self view]];
         [loadingPopup show];

         // ...
     }
 
     // ...
 
     -(void)scSearchFetcher: (SCSearchFetcher *)f
                fetchedList: (SearchResultList *)l
                   forSpecs: (SCSearchSpecs *)s
     {
         // ...
 
         [loadingPopup dismiss];
 
         // ...
     }
 */
@interface SCAlertStylePopup : SCPopup
{
    UIView *overlayView;
}

/**
 The color of the background rectangle.
 */
@property (retain) UIColor *color;

/**
 The alpha value behind the popup rectangle.  Default: 0.5.
 */
@property (readwrite) double alpha;

/**
 Radius for the rounded corners.  Default: 10.0.
 */
@property (readwrite) double cornerRadius;

@property (readwrite) double borderWidth;

/**
 Distance from the center of the containing view.
 
 Use to tweak popup position inside containing view,
 especially when the popup view contains text inputs or similar.
 */
@property (readwrite) double verticalShift;

/**
 Default value for 'color'.  Used in constructor.
 */
+(UIColor *)defaultColor;

/**
 Sets default color.
 */
+(void)setDefaultColor: (UIColor *)c;

/**
 Default value for 'alpha'.  Used in constructor.
 */
+(double)defaultAlpha;

/**
 Sets default alpha.
 */
+(void)setDefaultAlpha: (double)a;

/**
 Default value for 'cornerRadius'.  Used in constructor.
 */
+(double)defaultCornerRadius;

/**
 Sets default cornerRadius.
 */
+(void)setDefaultCornderRadius: (double)r;

@end