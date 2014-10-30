//
//  SCUIViewControllerCategory.h
//  project
//
//  Created by kimberly on 10/25/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#ifndef __IPHONE_7_0
#warning UIRectEdge not found, defining.
typedef NS_OPTIONS(NSUInteger, UIRectEdge) {
    UIRectEdgeNone  = 0,
    UIRectEdgeTop    = 1 << 0,
    UIRectEdgeLeft  = 1 << 1,
    UIRectEdgeBottom = 1 << 2,
    UIRectEdgeRight  = 1 << 3,
    UIRectEdgeAll    = UIRectEdgeTop | UIRectEdgeLeft | UIRectEdgeBottom | UIRectEdgeRight
};
#endif

@class SCWapViewController;

@interface UIViewController ( SlifterCore )

-(void)setNavBarColor: (UIColor *)color;
-(void)scWillBeShownInNavController;
-(void)scWillBeShownInTabController;
-(void)scWasShownInNavController;

@end


@interface UIViewController ( SlifterToBeRemoved )

-(void)setPresentationType: (int)pt;

@end


@interface UIViewController ( VCHierarchyClimber )

-(UIViewController *)currentTopViewController;
-(UIViewController *)leafwardNextInViewControllerHierarchy;
-(UIViewController *)topModalViewController;
-(UIViewController *)rootwardNextInViewControllerHierarchy;
-(UIViewController *)responderParent;
-(UIViewController *)responderAncestor;
-(UIViewController *)ancestorViewController;
-(UITabBarItem *)alternateTabBarItem;

@end


@interface UIViewController ( ios67Transition )

-(void)safeSetEdgesForExtendedLayout: (UIRectEdge)e;

@end


@interface NSObject ( BundleUtil )

-(NSObject *)objectFromNib: (NSString *)s
                   ofClass: (Class)c;

@end


@interface UINavigationItem ( SCNavigationItem )

-(void)setRightBarButtonTitle: (NSString *)s
                       action: (SEL)a
                       target: (id)t;

-(void)setBackTitle: (NSString *)s;

@end
