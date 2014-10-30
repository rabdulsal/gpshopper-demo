//
//  SCPopupControls.h
//  lunds
//
//  Created by kimberly on 8/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SCPopup.h"


@interface SCBaseTouchControl : UIControl

-(void)touchEndedInside;

@end



@class SCTextSelectControl;

@protocol SCTextSelectControlDelegate < NSObject >

-(void)scTextSelectControlBeganEditing: (SCTextSelectControl *)c;

@end


@interface SCTextSelectControl : SCBaseTouchControl
{
    UIPickerView *pickerView;
}

@property (assign) IBOutlet id<SCTextSelectControlDelegate> delegate;
@property (retain) NSArray *values;
@property (readonly) NSString *selectedValue;
@property (retain) SCPopup *popup;
@property (retain) IBOutlet UIView *inputAccessoryView;
@property (readonly) UILabel *label;
@property (readwrite, nonatomic) BOOL showsSelectionIndicator;

-(void)selectValue: (NSString *)s;

@end